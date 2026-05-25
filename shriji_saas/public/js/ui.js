const resizeHandle =
    document.getElementById("resizeHandle");

const bottomPanel =
    document.querySelector(".bottom-panel");

const topLayout =
    document.querySelector(".top-layout");

let isResizing = false;

resizeHandle.addEventListener("mousedown", () => {

    isResizing = true;

    document.body.style.userSelect = "none";
});

document.addEventListener("mousemove", (e) => {

    if (!isResizing) return;

    const windowHeight = window.innerHeight;

    const newBottomHeight =
        windowHeight - e.clientY;

    if (newBottomHeight < 120) return;

    if (newBottomHeight > 500) return;

    bottomPanel.style.height =
        newBottomHeight + "px";

    topLayout.style.flex =
        "none";

    topLayout.style.height =
        (windowHeight - newBottomHeight - 65) + "px";
});

document.addEventListener("mouseup", () => {

    isResizing = false;

    document.body.style.userSelect = "auto";
});
