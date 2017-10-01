// #include section
const express = require("express");
const path = require("path");
const body = require("body-parser");
const levenstein = require("./Modules/Levenstein.js");
const levensteinRecursive = require("./Modules/LevensteinRecursive");

// Basic Server Setup
const DATA = path.resolve("./Data/");
const app = express();
const PORT = 8080;

app.use(express.static(DATA));
app.use(body.json());

// Real stuff goes here
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
    res.json(levenstein.levensteinDistance(wordA, wordB));
});

app.post("/levensteinRecursive", function(req, res)
{
   let wordA = req.body.wordA;
   let wordB = req.body.wordB;

   res.status(201);
   res.json(levensteinRecursive.levensteinDistance(wordA, wordB));
});

app.listen(PORT);
console.log("Server launched");
