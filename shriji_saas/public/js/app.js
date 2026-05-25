let tabCount = 1;

let files = {

    "main.shriji": {

        code: "",

        output: "",

        explain: ""

    }

};

let currentFile = "main.shriji";

const tabsContainer =
    document.getElementById("tabsContainer");

const newTabButton =
    document.getElementById("newTabButton");

/* =========================
   🔄 SWITCH FILE
========================= */
function switchFile(fileName) {

    // 💾 SAVE ONLY IF FILE EXISTS
    if (files[currentFile])
    {
        files[currentFile].code =
            editor.getValue();

        files[currentFile].output =
            document.getElementById("resultBox").innerText;

        files[currentFile].explain =
            document.getElementById("explainBox").innerText;
    }

    // 🔄 SWITCH CURRENT FILE
    currentFile = fileName;

    document.getElementById(
    "editorTitle"
    ).innerText = fileName;

    // 📂 LOAD FILE DATA
    editor.setValue(
        files[fileName].code || ""
    );

    document.getElementById("resultBox").innerText =
        files[fileName].output || "";

    document.getElementById("explainBox").innerText =
        files[fileName].explain || "No explanation";

    // 🎨 ACTIVE TAB UI
    document
        .querySelectorAll(".file-tab")
        .forEach(t => {
            t.classList.remove("active");
        });

    const activeTab =
        document.querySelector(
            `[data-file="${fileName}"]`
        );

    if (activeTab)
    {
        activeTab.classList.add("active");
    }
}

/* =========================
   🧠 CREATE TAB
========================= */

function createTab(fileName) {

    const tab =
        document.createElement("div");

    tab.className = "file-tab";

    tab.setAttribute(
        "data-file",
        fileName
    );

    tab.innerHTML = `

        ${fileName}

        <span class="close-tab">
            ×
        </span>

    `;

    tab.onclick = (e) => {

        // ❌ CLOSE TAB
        if (
            e.target.classList.contains(
                "close-tab"
            )
        ) {

            // 🛡 MINIMUM 1 TAB
            if (
                Object.keys(files).length === 1
            )
            {
                return;
            }

            delete files[fileName];

            tab.remove();

            // 🔄 SWITCH SAFE FILE
            const remainingFiles =
                Object.keys(files);

            switchFile(
                remainingFiles[0]
            );

            return;
        }

        // 🔄 NORMAL SWITCH
        switchFile(fileName);

    };

    tabsContainer.appendChild(tab);

    return tab;
}

/* =========================
   🌸 DEFAULT TAB
========================= */

const defaultTab =
    createTab("main.shriji");

defaultTab.classList.add("active");

/* =========================
   ➕ NEW FILE
========================= */

newTabButton.onclick = () => {

    tabCount++;

    const fileName =
        "file" +
        tabCount +
        ".shriji";

    files[fileName] = {

        code: "",

        output: "",

        explain: ""

    };

    createTab(fileName);

    switchFile(fileName);
};
