const express = require("express");
const { exec } = require("child_process");
const fs = require("fs");
const path = require("path");

const app = express();
const PORT = 3000;

// 📁 Base directory for projects
const BASE_DIR = path.join(__dirname, "data/projects");

// static files
app.use(express.static("public"));
app.use(express.json());

/* =========================
   ▶ RUN CODE (MULTI-LINE FIX)
========================= */
app.post("/run", (req, res) => {

    const input = req.body.code;

    if (!input) {
        return res.json({
            output: "",
            explain: "",
            error: "No input given"
        });
    }

    const runtime = exec(
        `../shriji_lang/shrijilang`,
        (error, stdout, stderr) => {

            if (error) {
                return res.json({
                    output: "",
                    explain: "",
                    error: "Execution error"
                });
            }

            const jsonLines = stdout
                .split("\n")
                .filter(line =>
                    line.trim().startsWith("{") &&
                    line.trim().endsWith("}")
                );

            if (!jsonLines.length) {
                return res.json({
                    output: "",
                    explain: "",
                    error: "Runtime JSON response missing"
                });
            }

            const outputs = [];
            const explains = [];
            const errors = [];
            const corrected = [];

            for (const line of jsonLines)
            {
                const data = JSON.parse(line);


      if (data.output !== undefined && data.output !== "")
   {
            outputs.push(data.output);
   }

       if (data.explain !== undefined && data.explain !== "")
   {
            explains.push(data.explain);
   }

        if (data.error !== undefined && data.error !== "")
    {
            errors.push(data.error);
    }

        if (data.corrected !== undefined && data.corrected !== "")
     {
             corrected.push(data.corrected);
     }
        }

            res.json({
                  output: outputs.join("\n"),
                  explain: explains.join("\n\n"),
                  error: errors.join("\n"),
                  corrected: corrected.join("\n")
               });

        }
    );

    runtime.stdin.write(input + "\n");
    runtime.stdin.end();
});

/* =========================
   📁 CREATE PROJECT
========================= */
app.post("/create-project", (req, res) => {

    const { projectName } = req.body;

    if (!projectName) {
        return res.json({ error: "Project name required" });
    }

    const projectPath = path.join(BASE_DIR, projectName);

    if (fs.existsSync(projectPath)) {
        return res.json({ error: "Project already exists" });
    }

    fs.mkdirSync(projectPath, { recursive: true });

    res.json({
        message: "Project created",
        project: projectName
    });
});


/* =========================
   📄 CREATE FILE
========================= */
app.post("/create-file", (req, res) => {

    const { projectName, fileName } = req.body;

    if (!projectName || !fileName) {
        return res.json({ error: "Project and file name required" });
    }

    const filePath = path.join(BASE_DIR, projectName, fileName);

    if (fs.existsSync(filePath)) {
        return res.json({ error: "File already exists" });
    }

    fs.writeFileSync(filePath, "");

    res.json({
        message: "File created",
        file: fileName
    });
});


/* =========================
   💾 SAVE FILE
========================= */
app.post("/save-file", (req, res) => {

    const { projectName, fileName, content } = req.body;

    if (!projectName || !fileName) {
        return res.json({ error: "Missing data" });
    }

    const filePath = path.join(BASE_DIR, projectName, fileName);

    fs.writeFileSync(filePath, content || "");

    res.json({
        message: "File saved"
    });
});


/* =========================
   📖 READ FILE
========================= */
app.get("/read-file", (req, res) => {

    const { projectName, fileName } = req.query;

    const filePath = path.join(BASE_DIR, projectName, fileName);

    if (!fs.existsSync(filePath)) {
        return res.json({ error: "File not found" });
    }

    const content = fs.readFileSync(filePath, "utf-8");

    res.json({
        content: content
    });
});


/* =========================
   📂 LIST FILES
========================= */
app.get("/list-files", (req, res) => {

    const { projectName } = req.query;

    if (!projectName) {
        return res.json({ error: "Project name required" });
    }

    const projectPath = path.join(BASE_DIR, projectName);

    if (!fs.existsSync(projectPath)) {
        return res.json({ error: "Project not found" });
    }

    const files = fs.readdirSync(projectPath);

    res.json({
        files: files
    });
});


/* =========================
   🚀 START SERVER
========================= */
app.listen(PORT, () => {
    console.log(`🌸 Shriji SaaS running at http://localhost:${PORT}`);
});
