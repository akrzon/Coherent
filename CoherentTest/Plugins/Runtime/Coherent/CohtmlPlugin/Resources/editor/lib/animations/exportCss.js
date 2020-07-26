"use strict";Object.defineProperty(exports,"__esModule",{value:!0});var main_1=require("../../scripts/main"),function_helpers_1=require("../function_helpers"),exportCssModule;!function(e){function r(e){var r={filterProperties:{}};for(var t in e)for(var n in e[t])r.filterProperties[n]||(r.filterProperties[n]=e[t][n]);return r}function t(e){var r="",t="",a="",i="",o="",s="",u="";for(var l in e.keyframes){var f=e.keyframes[l],m=e.animationsData[l];for(var c in f){var p=f[c],v=m[c],d=n(p),k=v.name;r+=k&&""!==k?u+v.name:u+l+"_"+c,t+=u+d.totalTimeToPlay+"ms",a+=u+d.start+"ms",i+=u+v.timing,o+=u+v.iteration,s+=u+v.direction,u=", ",~~d.end>~~y.totalAnimationTime&&(y.totalAnimationTime=~~d.end)}}return{names:r,end:t,start:a,timing:i,iteration:o,direction:s}}function n(e){var r=Object.keys(e),t=r[r.length-1]-r[0];return{end:r[r.length-1],start:r[0],totalTimeToPlay:t}}function a(e,r,t){var n="",a=t.end-t.start;for(var y in e){var d,k=v(parseFloat(y)-t.start,a);switch(r){case"geometry":d=i(e[y]);break;case"transform":d=f(e[y]);break;case"transform-origin":d=m(e[y]);break;case"-webkit-filter":d=c(r,e[y]);break;case"boxShadow":d=p(r,e[y]);break;case"backgroundColor":d=u(r,e[y]);break;case"styles":d="color"===e[y].property?l(r,e[y]):o(e[y]);break;case"font":d=s(e[y]);break;default:console.error("Loop keyframes error!")}n+=k+"%   { "+d.property+": "+d.value+"; }\n"}return n}function i(e){return{property:e.property,value:e.values[0]}}function o(e){return{property:function_helpers_1.default.convertJsToCssProperty(e.property),value:e.values[0]}}function s(e){return{property:function_helpers_1.default.convertJsToCssProperty(e.property),value:e.values[0]}}function u(e,r){return{property:"background-color",value:r.values[0]}}function l(e,r){return{property:"color",value:r.values[0]}}function f(e){return{property:e.property,value:e.values[0]}}function m(e){return{property:e.property,value:e.values[0]}}function c(e,r){return{property:e,value:function_helpers_1.default.buildFilterProps(r,!0)}}function p(e,r){return{property:"box-shadow",value:r.values[0]}}function v(e,r){return 0===e&&0===r?100:(e/r*100).toFixed(2)}var y;e.exportCss=function(e,r){return y=main_1.default.openFiles[r].runtimeEditor,y.totalAnimationTime=0,_(e)};var d=function(e,r){if(e)return'custom-metadata: "{"'+r+'":'+JSON.stringify(e.keyframes["-webkit-filter"])+'}";\n}'},k=function(e,r){return'transforms-metadata: "{"'+r+'":'+JSON.stringify(e.keyframes.transform)+'}";\n'},_=function(e){var i="",o=y.scene.animationClasses,s=main_1.default.onSelectedFileType.publishPage;for(var u in e){var l="}\n",f="",m=e[u],c=void 0;if(m.keyframes["-webkit-filter"]){var p=o[u];l=s?"}\n":d(p,u),m.keyframes["-webkit-filter"]=r(m.keyframes["-webkit-filter"]);var v=Object.keys(m.animationsData["-webkit-filter"])[0],_=m.animationsData["-webkit-filter"][v];m.animationsData["-webkit-filter"]={filterProperties:_}}else l="}\n";if(m.keyframes.transform){var b=y.scene.animationClasses[u];f=s?"":k(b,u)}if(c=t(m),m.className){i+="."+m.className+" {\nanimation-fill-mode: forwards;\nanimation-name: "+c.names+";\nanimation-duration: "+c.end+";\nanimation-timing-function: "+c.timing+";\nanimation-delay: "+c.start+";\nanimation-iteration-count: "+c.iteration+";\nanimation-direction: "+c.direction+";\n"+f+l;for(var T in m.keyframes){var g=m.keyframes[T],P=m.animationsData[T];for(var w in g){var C=g[w],h=P[w],S=a(C,T,n(C));i+="@keyframes "+(h.name&&""!==h.name?h.name:T+"_"+w+"_"+m.id)+"{\n"+S+"}\n "}}}}return""!==i?'<style id="coui_animations_block">\n'+main_1.default.environmentProperties.CSS_ANIMATIONS_MARK_START+"\n"+i+main_1.default.environmentProperties.CSS_ANIMATIONS_MARK_END+"\n</style>":""}}(exportCssModule||(exportCssModule={})),exports.default=exportCssModule;