from flask import Flask, render_template, request, jsonify
from collections import OrderedDict
import json

app = Flask(__name__)

cache_store = {
    "policy": "LRU",
    "capacity": 3,
    "data": OrderedDict(),
    "freq": {},
    "hits": 0,
    "misses": 0,
    "history": []
}

def lru_get(key):
    if key not in cache_store["data"]:
        cache_store["misses"] += 1
        return None, "miss"
    cache_store["data"].move_to_end(key, last=False)
    cache_store["hits"] += 1
    return cache_store["data"][key], "hit"

def lru_put(key, value):
    if key in cache_store["data"]:
        cache_store["data"].move_to_end(key, last=False)
        cache_store["data"][key] = value
    else:
        if len(cache_store["data"]) >= cache_store["capacity"]:
            evicted = next(reversed(cache_store["data"]))
            del cache_store["data"][evicted]
            cache_store["history"].append(f"Evicted key {evicted} (LRU)")
        cache_store["data"][key] = value
        cache_store["data"].move_to_end(key, last=False)

def lfu_get(key):
    if key not in cache_store["data"]:
        cache_store["misses"] += 1
        return None, "miss"
    cache_store["freq"][key] = cache_store["freq"].get(key, 0) + 1
    cache_store["hits"] += 1
    return cache_store["data"][key], "hit"

def lfu_put(key, value):
    if key in cache_store["data"]:
        cache_store["data"][key] = value
        cache_store["freq"][key] = cache_store["freq"].get(key, 0) + 1
    else:
        if len(cache_store["data"]) >= cache_store["capacity"]:
            evicted = min(cache_store["freq"], key=lambda k: cache_store["freq"][k])
            del cache_store["data"][evicted]
            del cache_store["freq"][evicted]
            cache_store["history"].append(f"Evicted key {evicted} (LFU)")
        cache_store["data"][key] = value
        cache_store["freq"][key] = 1

def fifo_get(key):
    if key not in cache_store["data"]:
        cache_store["misses"] += 1
        return None, "miss"
    cache_store["hits"] += 1
    return cache_store["data"][key], "hit"

def fifo_put(key, value):
    if key in cache_store["data"]:
        cache_store["data"][key] = value
    else:
        if len(cache_store["data"]) >= cache_store["capacity"]:
            evicted = next(iter(cache_store["data"]))
            del cache_store["data"][evicted]
            cache_store["history"].append(f"Evicted key {evicted} (FIFO)")
        cache_store["data"][key] = value

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/api/config", methods=["POST"])
def config():
    body = request.get_json()
    cache_store["policy"] = body.get("policy", "LRU")
    cache_store["capacity"] = int(body.get("capacity", 3))
    cache_store["data"] = OrderedDict()
    cache_store["freq"] = {}
    cache_store["hits"] = 0
    cache_store["misses"] = 0
    cache_store["history"] = []
    return jsonify({"status": "ok", "policy": cache_store["policy"], "capacity": cache_store["capacity"]})

@app.route("/api/put", methods=["POST"])
def put():
    body = request.get_json()
    key = int(body.get("key"))
    value = int(body.get("value"))
    policy = cache_store["policy"]

    if policy == "LRU":
        lru_put(key, value)
    elif policy == "LFU":
        lfu_put(key, value)
    elif policy == "FIFO":
        fifo_put(key, value)

    cache_store["history"].append(f"PUT key={key} value={value}")
    return jsonify(get_state())

@app.route("/api/get", methods=["POST"])
def get():
    body = request.get_json()
    key = int(body.get("key"))
    policy = cache_store["policy"]

    if policy == "LRU":
        value, status = lru_get(key)
    elif policy == "LFU":
        value, status = lfu_get(key)
    elif policy == "FIFO":
        value, status = fifo_get(key)

    cache_store["history"].append(f"GET key={key} -> {status.upper()}")
    return jsonify({"status": status, "value": value, **get_state()})

@app.route("/api/state", methods=["GET"])
def state():
    return jsonify(get_state())

def get_state():
    total = cache_store["hits"] + cache_store["misses"]
    hit_rate = round((cache_store["hits"] / total * 100), 1) if total > 0 else 0
    items = []
    for k, v in cache_store["data"].items():
        items.append({
            "key": k,
            "value": v,
            "freq": cache_store["freq"].get(k, 1)
        })
    return {
        "policy": cache_store["policy"],
        "capacity": cache_store["capacity"],
        "size": len(cache_store["data"]),
        "hits": cache_store["hits"],
        "misses": cache_store["misses"],
        "hit_rate": hit_rate,
        "items": items,
        "history": cache_store["history"][-10:]
    }

if __name__ == "__main__":
    app.run(debug=True)