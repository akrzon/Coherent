"use strict";Object.defineProperty(exports,"__esModule",{value:!0});var function_helpers_1=require("./function_helpers"),main_1=require("../scripts/main"),units_conversion_1=require("../scripts/helpers/units_conversion"),SceneInteract;!function(e){function t(e){r(),$("#sceneTree").jstree("deselect_all");var t="",n="",a=0,i=0,l=function(e){var o=!1;e.pageX<a?t="left":e.pageX>a&&(t="right"),e.pageY<i?n="top":e.pageY>i&&(n="bottom"),"left"===t&&parseFloat(U.style.width)<=1&&(I=!1,K=!0,o=!0),"right"===t&&parseFloat(U.style.width)<=1&&(I=!0,K=!1,o=!0),"top"===n&&parseFloat(U.style.height)<=1&&(W=!0,z=!1,o=!0),"bottom"===n&&parseFloat(U.style.height)<=1&&(W=!1,z=!0,o=!0),o&&E(e),a=e.pageX,i=e.pageY},s=function(){o(),document.removeEventListener("mousemove",l),document.removeEventListener("mouseup",s)};document.addEventListener("mousemove",l),document.addEventListener("mouseup",s),E(xe)}function o(){I=!1,K=!1,W=!1,z=!1}function n(e){o(),i(),r()}function r(){document.removeEventListener("mousemove",y),document.removeEventListener("mouseup",F),document.addEventListener("mousemove",y),document.addEventListener("mouseup",F)}function a(e,t,o,n,r){for(var a=0;a<e.length;a++)e[a].addEventListener("mousedown",function(e){e.preventDefault(),e.stopPropagation(),E(e)}),e[a].addEventListener("mouseover",function(){W=t,K=o,I=n,z=r}),e[a].addEventListener("mouseout",function(){W=!1,K=!1,I=!1,z=!1})}function i(){ie=U.getElementsByClassName("top-left-corner"),le=U.getElementsByClassName("top-right-corner"),se=U.getElementsByClassName("bottom-left-corner"),de=U.getElementsByClassName("bottom-right-corner"),ue=U.getElementsByClassName("left-center"),pe=U.getElementsByClassName("right-center"),ge=U.getElementsByClassName("top-center"),me=U.getElementsByClassName("bottom-center"),a(ie,!0,!0,!1,!1),a(le,!0,!1,!0,!1),a(se,!1,!0,!1,!0),a(de,!1,!1,!0,!0),a(ue,!1,!0,!1,!1),a(pe,!1,!1,!0,!1),a(ge,!0,!1,!1,!1),a(me,!1,!1,!1,!0)}function l(){if("create"!==Se){var e=main_1.default.openFiles[ae].runtimeEditor.mappedWidgets[re.id].widget.geometry,t=function_helpers_1.default.getUnitStyle(e.width),o=function_helpers_1.default.getUnitStyle(e.height),n=function_helpers_1.default.getUnitStyle(e.top),r=function_helpers_1.default.getUnitStyle(e.left),a=getComputedStyle(re.parentElement,null),i=parseFloat(a.getPropertyValue("width")),l=parseFloat(a.getPropertyValue("height")),s=re.style;if("%"===n){var d=units_conversion_1.default.convertPercentToPixel(parseFloat(e.top),l);s.top=d+"px"}if("%"===r){var u=units_conversion_1.default.convertPercentToPixel(parseFloat(e.left),i);s.left=u+"px"}if("%"===t){var p=units_conversion_1.default.convertPercentToPixel(parseFloat(e.width),i);s.width=p+"px"}if("%"===o){var g=units_conversion_1.default.convertPercentToPixel(parseFloat(e.height),l);s.height=g+"px"}}}function s(){return this}function d(){return this}function u(){return this}function p(){return this}function g(){return this}function m(){return this}function f(){return this}function c(){return this}function h(e){return new WebKitCSSMatrix(window.getComputedStyle(e).webkitTransform)}function E(e){Pe=re.style.width,we=re.style.height,X=$("#scene")[0],main_1.default.openFiles[ae].runtimeEditor.onResizeElStart(),fe=e.clientX,ce=e.clientY,he=parseFloat(units_conversion_1.default.convertUnitsToPixel(re.id,re.style.width,"width")),Ee=parseFloat(units_conversion_1.default.convertUnitsToPixel(re.id,re.style.height,"height")),_(e);var t=I||z||W||K;Ce={x:ye,y:ve,cx:e.clientX,cy:e.clientY,isResizing:t,onTopEdge:W,onLeftEdge:K,onRightEdge:I,onBottomEdge:z},Z=parseFloat(getComputedStyle(re,null).getPropertyValue("border-left-width")),D=parseFloat(getComputedStyle(re,null).getPropertyValue("border-right-width")),j=parseFloat(getComputedStyle(re,null).getPropertyValue("border-top-width")),A=parseFloat(getComputedStyle(re,null).getPropertyValue("border-bottom-width")),H=parseFloat(getComputedStyle(re,null).getPropertyValue("margin-left")),O=parseFloat(getComputedStyle(re,null).getPropertyValue("margin-right")),G=parseFloat(getComputedStyle(re,null).getPropertyValue("margin-top")),J=parseFloat(getComputedStyle(re,null).getPropertyValue("margin-bottom")),Q=parseFloat(getComputedStyle(re,null).getPropertyValue("padding-left")),ee=parseFloat(getComputedStyle(re,null).getPropertyValue("padding-right")),te=parseFloat(getComputedStyle(re,null).getPropertyValue("padding-top")),oe=parseFloat(getComputedStyle(re,null).getPropertyValue("padding-bottom")),Re=D+Z+H+O+Q+ee,be=A+j+G+J+te+te,Ce.onBottomEdge&&Ce.onLeftEdge?(l(),u()):Ce.onTopEdge&&Ce.onRightEdge?(l(),p()):Ce.onBottomEdge||Ce.onRightEdge?(l(),s()):(Ce.onTopEdge||Ce.onLeftEdge)&&(l(),d())}function y(e){_(e)}function v(){Le.transform(re);var e=function_helpers_1.default.getTransformedElMaskPos(re);U.style.width=e.width+"px",U.style.height=e.height+"px",U.style.top=e.top+"px",U.style.left=e.left+"px"}function _(e){var t,o,n;if(Ce&&Ce.isResizing){var r,a,i=main_1.default.openFiles[ae].runtimeEditor;if(window.requestAnimationFrame(function(){v()}),_e=e.clientX-fe,Fe=e.clientY-ce,("create"===i.interactElementsState||Ee===he)&&e.shiftKey&&(Ce.onLeftEdge&&Ce.onTopEdge||Ce.onLeftEdge&&Ce.onBottomEdge||Ce.onRightEdge&&Ce.onTopEdge||Ce.onRightEdge&&Ce.onBottomEdge)&&(i.equalProportion=!0,Fe=_e,Ce.onRightEdge&&Ce.onTopEdge&&(Fe=-_e)),q=main_1.default.openFiles[ae].runtimeEditor.tab.sceneTransformMatrix[0],Ce.onRightEdge&&"auto"!==Pe){if(e.shiftKey&&(Ce.onBottomEdge||Ce.onTopEdge)){var l=1,s=_e;Ee>he&&(s=Fe,l=he/Ee,Ce.onTopEdge&&(s=-s)),t=he+s*l/q-Re}else t=he+_e/q-Re;t<0&&(t=0),re.style.width=t+"px"}if(Ce.onBottomEdge&&"auto"!==we){if(e.shiftKey&&Ce.onRightEdge){var l=1,s=Fe;Ee<he&&(s=_e,l=Ee/he),o=Ee+s*l/q-be}else o=Ee+Fe/q-be;o<0&&(o=0),re.style.height=o+"px"}if(Ce.onLeftEdge&&"auto"!==Pe){var s=_e,l=1;if(e.shiftKey&&Ce.onBottomEdge||Ce.onTopEdge){Ce.onBottomEdge&&(s=-s),he<Ee&&(s=Fe,l=he/Ee);var d=he+s*l/q;Ce.onTopEdge&&(d=he-s*l/q),t=Math.max(Math.floor(d),Te)}else t=Math.max(Math.floor(he-_e/q),Te);if(e.shiftKey&&Ce.onBottomEdge){var u=void 0;u=he>Ee?Ee+s*(l=Ee/he)/q:Ee+s/q,o=Math.max(Math.floor(u),Be),n=getComputedStyle(re,null),r=parseFloat(n.getPropertyValue("height"))-o,a=parseFloat(n.getPropertyValue("top"))+r,re.style.height=o-be+"px"}if(t>=Te+Re){n=getComputedStyle(re,null);var p=parseFloat(n.getPropertyValue("width"))-t,g=parseFloat(n.getPropertyValue("left"))+p;re.style.width=t-Re+"px",re.style.left=g+Re+"px","create"===i.interactElementsState&&re.style.width!==re.style.height&&e.shiftKey&&Ce.onBottomEdge&&Ce.onLeftEdge&&(re.style.height=parseFloat(t)+"px")}}if(Ce.onTopEdge&&"auto"!==we){var l=1,s=Fe;if(he>Ee?(s=_e,l=Ee/he):Ce.onRightEdge&&(s=-s),e.shiftKey&&(Ce.onLeftEdge||Ce.onRightEdge)?(Ce.onLeftEdge&&(s=-s),o=Math.max(Math.floor(Ee+s*l/q),Be)):o=Math.max(Math.floor(Ee-Fe/q),Be),o>=Be+be&&(n=getComputedStyle(re,null),r=parseFloat(n.getPropertyValue("height"))-o,a=parseFloat(n.getPropertyValue("top"))+r,re.style.height=o-be+"px",re.style.top=a+be+"px","create"===i.interactElementsState&&re.style.width!==re.style.height&&e.shiftKey&&Ce.onTopEdge&&Ce.onRightEdge)){var m=parseFloat(re.style.width)-parseFloat(re.style.height);re.style.height=parseFloat(t)+"px",re.style.top=parseFloat(re.style.top)-m+"px"}}return k=!0,void main_1.default.openFiles[ae].runtimeEditor.onResizeElMove(re)}k=!1,U.style.cursor=I&&z||K&&W?"nwse-resize":I&&W||z&&K?"nesw-resize":I||K?"ew-resize":z||W?"ns-resize":"default"}function F(e){Ce&&(Ce.onBottomEdge&&Ce.onLeftEdge?f():Ce.onTopEdge&&Ce.onRightEdge?c():Ce.onTopEdge||Ce.onLeftEdge?m():(Ce.onBottomEdge||Ce.onRightEdge)&&g()),Ce=null,!0===k&&(main_1.default.openFiles[ae].runtimeEditor.onResizeElEnd(re,e),k=!1)}function P(e){for(var t=document.getElementsByClassName(e),o=0;o<t.length;o++)t[o].addEventListener("mousedown",function(e){e.stopPropagation(),b(e)})}function w(e){P("bottom-left-rotate"),P("top-left-rotate"),P("bottom-right-rotate"),P("top-right-rotate"),document.getElementById("center-pane").addEventListener("mouseup",V),document.getElementById("center-pane").addEventListener("mousemove",M)}function x(e){if(Ve){main_1.default.openFiles[ae].runtimeEditor.onRotateElMove();var t,o;t=C(e);var n=We+(o=t-Ke);isNaN(n)&&(n=We);var r=ke+o;isNaN(r)&&(r=ke),Ke=t;var a="rotateZ("+r+"rad)",i=/rotateZ\((.*?)\)/,l=re.style.WebkitTransform;if(!l.match(i)){var s=main_1.default.openFiles[ae].runtimeEditor;s._skipUndoRedoSteps=1;var d=s.mappedWidgets[ne].widget;return void s._setTransform(null,d,ne,"transform","rotateZ","0deg")}var u=l=l.replace(i,a);U.style.WebkitTransform="rotateZ("+n+"rad)",re.style.WebkitTransform=u,We=n,ke=r}}function S(e){for(var t=e,o=t.offsetLeft,n=t.offsetTop;t=t.offsetParent;)o+=t.offsetLeft;for(var r=U;r=r.offsetParent;)n+=r.offsetTop;return[o,n]}function L(e){return[e.offsetWidth,e.offsetHeight]}function T(e){return[S(e)[0]+L(e)[0]/2,S(e)[1]+L(e)[1]/2]}function B(e){return[e.pageX,e.pageY]}function C(e){var t;Me=S(re),Ne=L(re),Ie=T(re),ze=B(e);try{t=Math.atan2(ze[1]-Ie[1],ze[0]-Ie[0])}catch(e){console.error(e)}return(t+=Ue/4)<0&&(t+=Ue),t}function R(e,t){t?(e.preventDefault(),Ke=C(e),Ve=!0):Ve=!1}function b(e){main_1.default.openFiles[ae].runtimeEditor.onRotateElStart();var t=N(U),o=N(re);We=t.rad,ke=o.rad,X=$("#scene")[0],Y=h(X),R(e,!0)}function V(e){var t={rad:ke,deg:function_helpers_1.default.toDegrees(ke)};main_1.default.openFiles[ae].runtimeEditor.onRotateElEnd(re,t),R(e,!1)}function M(e){x(e)}function N(e,t){var o={rad:0,deg:0},n=window.getComputedStyle(e,null).getPropertyValue("-webkit-transform");return(n=n.match("matrix\\((.*)\\)"))?void 0!==(n=n[1].split(","))[0]&&void 0!==n[1]&&(o.rad+=Math.atan2(n[1],n[0]),o.deg+=parseFloat((180*o.rad/Math.PI).toFixed(1))):null!==e.id&&""!==e.id&&main_1.default.openFiles[main_1.default.selectedEditor].runtimeEditor.mappedWidgets[e.id].widget.transform&&(o.deg=parseFloat(main_1.default.openFiles[main_1.default.selectedEditor].runtimeEditor.mappedWidgets[e.id].widget.transform.rotateZ)||0,o.rad=function_helpers_1.default.toRadians(o.deg)),o}var I,z,K,W,k,U,X,Y,q,Z,D,j,A,H,O,G,J,Q,ee,te,oe,ne,re,ae,ie,le,se,de,ue,pe,ge,me,fe,ce,he,Ee,ye,ve,_e,Fe,Pe,we,xe,Se,Le,Te=0,Be=0,Ce=null,Re=0,be=0;e.Interact=function(e,o,r,a){ne=e.id,re=e,ae=o,xe=a,Se=r,Le=main_1.default.openFiles[main_1.default.selectedEditor].runtimeEditor.transform,U=document.getElementsByClassName(r+"-corners")[0],"rotate"===r?(document.removeEventListener("mousemove",y),document.removeEventListener("mouseup",F),w()):"create"===r?(document.getElementById("center-pane").removeEventListener("mouseup",V),document.getElementById("center-pane").removeEventListener("mousemove",M),t()):"resize"===r&&(document.getElementById("center-pane").removeEventListener("mouseup",V),document.getElementById("center-pane").removeEventListener("mousemove",M),n())};var Ve=!1,Me=[],Ne=[],Ie=[],ze=[],Ke=0,We=0,ke=0,Ue=2*Math.PI}(SceneInteract||(SceneInteract={})),exports.default=SceneInteract;