"use strict";function createVDOM(e){var t=document.createElement("div");t.innerHTML=e;var r=[].slice.call(t.children);return r.forEach(function(e,t){e.style.top=34*t+"px",e.setAttribute("vList-index",String(t))}),r}Object.defineProperty(exports,"__esModule",{value:!0}),exports.createVDOM=createVDOM;