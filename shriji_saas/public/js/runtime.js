/* =========================
   ⚡ AUTO RUN SYSTEM
========================= */

let timeout = null;

let isRunning = false;

function autoRun() {

    clearTimeout(timeout);

    timeout = setTimeout(() => {
        runCode();
    }, 500);
}

/* =========================
   ▶ RUN CODE
========================= */

function runCode() {

    const runButton =
        document.getElementById("runButton");

    const code = editor.getValue();

    if (isRunning) {
        return;
    }

    // 🧹 EMPTY CHECK
    if (!code.trim()) {

        document.getElementById("resultBox").innerText = "";

        document.getElementById("correctBox").innerText = "";

        document.getElementById("errorBox").innerText = "";

        document.getElementById("hintBox").innerText = "";

        return;
    }

    isRunning = true;

    runButton.disabled = true;

    runButton.innerText = "Running...";

    // ⏳ LOADING
    document.getElementById("resultBox").innerText =
        "Running...";

    fetch("/run", {

        method: "POST",

        headers: {
            "Content-Type": "application/json"
        },

        body: JSON.stringify({
            code: code
        })

    })

    .then(res => res.json())

.then(data => {

    let finalOutput = data.output || "";

    if (finalOutput.length > 4000)
    {
        finalOutput =
            finalOutput.substring(0, 4000) +
            "\n\n[OUTPUT LIMIT REACHED]";
    }

    document.getElementById("resultBox").innerText =
        finalOutput;

    document.getElementById("correctBox").innerText = "";

    let explainText = "";

    if (data.corrected)
    {
        explainText +=
            "Corrected:\n" +
            data.corrected +
            "\n\n";
    }

    if (data.explain)
    {
        explainText +=
            data.explain + "\n\n";
    }

    if (data.error)
    {
        let cleanError = data.error;

        if (cleanError.includes("{"))
        {
            cleanError =
                cleanError.split("{")[0];
        }

        explainText +=
            "Error:\n" +
            cleanError.trim();
    }

    document.getElementById("explainBox").innerText =
        explainText || "No explanation";

})

.finally(() => {

    isRunning = false;

    runButton.disabled = false;

    runButton.innerText = "▶ Run";

});

}
