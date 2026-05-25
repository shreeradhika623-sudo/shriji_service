/* =========================
   📁 LOAD FILES
========================= */

async function loadFiles() {

    const res = await fetch("/list-files?projectName=demo");
    const data = await res.json();

    const list = document.getElementById("fileList");
    list.innerHTML = "";

    data.files.forEach(file => {

        const li = document.createElement("li");
        li.textContent = file;

        li.onclick = async () => {

            window.currentFile = file;

            const res = await fetch(`/read-file?projectName=demo&fileName=${file}`);
            const data = await res.json();

            editor.setValue(data.content);
        };

        list.appendChild(li);
    });
}

/* =========================
   💾 SAVE FILE
========================= */

async function saveFile() {

    if (!window.currentFile) {
        alert("Select file first");
        return;
    }

    const content = editor.getValue();

    await fetch("/save-file", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({
            projectName: "demo",
            fileName: window.currentFile,
            content: content
        })
    });

    alert("Saved!");
}
