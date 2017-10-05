const abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

var levenstein = undefined;
var levensteinRecursive = undefined;
var damerau = undefined;
var damerauRecursive = undefined;

function setFunctions(lev, levRec, dam, damRec)
{
    levenstein = lev;
    levensteinRecursive = levRec;
    damerau = dam;
    damerauRecursive = damRec;
}

function test(wordLen, repeats)
{
    let res = {levenstein: 0, levensteinRecursive: 0, damerauLevenstein: 0, damerauLevensteinRecursive: 0};

    for(let times = 0; times < repeats; times++)
    {
        let wordA = "";
        let wordB = "";
        for(let i = 0; i < wordLen; i++)
        {
            wordA += abc.charAt(Math.floor(Math.random() * abc.length));
            wordB += abc.charAt(Math.floor(Math.random() * abc.length));
        }

        console.log("wordA: " + wordA +"\nwordB: " + wordB);

        res.levenstein -= Date.now();
        levenstein(wordA, wordB);
        res.levenstein += Date.now();

        res.levensteinRecursive -= Date.now();
        levensteinRecursive(wordA, wordB);
        res.levensteinRecursive += Date.now();

        res.damerauLevenstein -= Date.now();
        damerau(wordA, wordB);
        res.damerauLevenstein += Date.now();

        res.damerauLevensteinRecursive -= Date.now();
        damerauRecursive(wordA, wordB);
        res.damerauLevensteinRecursive += Date.now();
    }

    res.levenstein /= repeats;
    res.levensteinRecursive /= repeats;
    res.damerauLevenstein /= repeats;
    res.damerauLevensteinRecursive /= repeats;

    return res;
}

module.exports.test = test;
module.exports.setFunctions = setFunctions;