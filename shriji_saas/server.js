
const express = require("express");
const { exec } = require("child_process");
const fs = require("fs");
const path = require("path");

const app = express();
const PORT = process.env.PORT || 3000;
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

    const uniqueName =
    "temp_" + Date.now() + ".sri";

     const tempFile =
         path.join(__dirname, uniqueName);

     const sriPath = path.join(
         __dirname,
           "../shrijilang/sri"
  );

fs.writeFileSync(tempFile, input);

exec(

    `${sriPath} ${tempFile}`,

    {
        timeout: 3000,
        maxBuffer: 1024 * 1024
    },

    (error, stdout, stderr) => {

console.log("========== RUN ==========");

console.log("STDOUT:");
console.log(stdout);

console.log("STDERR:");
console.log(stderr);

console.log("ERROR:");
console.log(error);


    fs.unlinkSync(tempFile);

    if (stderr)
    {
        stdout += "\nERROR:\n" + stderr;
    }

    const lines = stdout.split("\n");

    let output = [];
    let explain = [];
    let errorText = [];

    let mode = "";

    for (const raw of lines)
    {
        const clean = raw.trim();

        if (clean.startsWith("OUTPUT:"))
        {
            mode = "output";
            continue;
        }

        if (clean.startsWith("EXPLAIN:"))
        {
            mode = "explain";
            continue;
        }

        if (clean.startsWith("ERROR:"))
        {
            mode = "error";
            continue;
        }

        if (
            clean.startsWith("DETAILS:") ||
            clean.startsWith("SUGGESTION:") ||
            clean.startsWith("JSON:")
        )
        {
            continue;
        }

        if (clean === "")
        {
            continue;
        }

        if (mode === "output")
        {
            output.push(clean);
        }

        if (mode === "explain")
        {
            explain.push(clean);
        }

        if (mode === "error")
        {
            errorText.push(clean);
        }
    }

    res.json({
        output: output.join("\n"),
        explain: explain.join("\n"),
        error: errorText.join("\n")
    });
  });
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
