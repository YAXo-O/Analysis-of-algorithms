const express = require("express");
const path = require("path");
const body = require("body-parser");

const DATA = path.resolve("./Data/");
const app = express();
const PORT = 8080;

app.use(express.static(DATA));
app.use(body.json());

app.get("/", function(req, res)
{
    let index = DATA + "index.html";
    res.sendFile(index);
});

app.post("/levenstein", function(req, res)
{
    let wordA = req.body.wordA;
    let wordB = req.body.wordB;

    res.status(201);
    res.json(levenstein(wordA, wordB));
});

app.listen(PORT);
console.log("Server launched");

//--- functions section
function levenstein(wordA, wordB)
{
    return {result: [0, 0, 1, 1], x: 2, y: 2};
}