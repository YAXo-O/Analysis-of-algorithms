const Http = fetches();

const button = document.getElementById("doTests");
button.addEventListener("click", function()
{
    Http.FetchGet("/testResults")
        .then((response) =>
    {
        fill(response.ten, 10);
        fill(response.fifty, 50);
        fill(response.hundread, 100);
    });
});

function fill(data, index)
{
    const l = document.getElementById("l" + index);
    const lr = document.getElementById("lr" + index);
    const d = document.getElementById("d" + index);
    const dr = document.getElementById("dr" + index);

    l.innerHTML = data.levenstein;
    lr.innerHTML = data.levensteinRecursive;
    d.innerHTML = data.damerauLevenstein;
    dr.innerHTML = data.damerauLevensteinRecursive;
}