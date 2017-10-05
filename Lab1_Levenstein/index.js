// #include section
const express = require("express");
const path = require("path");
const body = require("body-parser");
const levenstein = require("./Modules/Levenstein.js");
const levensteinRecursive = require("./Modules/LevensteinRecursive");
const damerauLevenstein = require("./Modules/DamerauLevenstein");
const damerauLevensteinRecursive = require("./Modules/DamerauLevensteinRecursive");
const test = require("./Modules/test.js");

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

app.post("/damerauLevenstein", function(req, res)
{
    let wordA = req.body.wordA;
    let wordB = req.body.wordB;

    res.status(201);
    res.json(damerauLevenstein.damerauLevenstein(wordA, wordB));
});

app.post("/damerauLevensteinRecursive", function(req, res)
{
    let wordA = req.body.wordA;
    let wordB = req.body.wordB;

    res.status(201);
    res.json(damerauLevensteinRecursive.damerauLevenstein(wordA, wordB));
});

app.get("/tests", function(req, res)
{
    let tests = DATA + "/tests.html";
    res.sendFile(tests);
});

app.get("/testResults", function(req, res)
{
    const testRepeat = 10;

    test.setFunctions(levenstein.levensteinDistance, levensteinRecursive.levensteinDistance,
                      damerauLevenstein.damerauLevenstein, damerauLevensteinRecursive.damerauLevenstein);

    res.status(201);
    res.json({ten: test.test(10, testRepeat), fifty: test.test(50, testRepeat), hundread: test.test(100, testRepeat)});
});

app.listen(PORT);
console.log("Server launched");
