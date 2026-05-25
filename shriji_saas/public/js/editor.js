/* =========================
   🧠 EDITOR SETUP
========================= */

const editor = CodeMirror.fromTextArea(
    document.getElementById("code"),
    {
        lineNumbers: true,
        theme: "dracula",
        mode: "javascript"
    }
);

/* =========================
   ⌨️ CTRL + ENTER RUN
========================= */

document.getElementById("code").addEventListener("keydown", function(e) {
    if (e.ctrlKey && e.key === "Enter") {
        runCode();
    }
});
