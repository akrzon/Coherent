"use strict";Object.defineProperty(exports,"__esModule",{value:!0});var types_1=require("./types"),enums_1=require("../enums"),function_helpers_1=require("../function_helpers"),main_1=require("../../scripts/main"),importCssHandler;!function(e){function r(e,r){for(var t in e)!function(t){if(!r[t])return"continue";var a=Object.keys(e[t]);a.filter(function(n){if(!r[t].animationsData["-webkit-filter"][n]){var i=r[t].animationsData["-webkit-filter"].filterProperties,o=a.length;r[t].animationsData["-webkit-filter"][a[0]]=i;for(var s=r[t].animationsData["-webkit-filter"][a[0]],l=1;l<o;l++)r[t].animationsData["-webkit-filter"][a[l]]=s;r[t].keyframes["-webkit-filter"]=e[t],delete r[t].animationsData["-webkit-filter"].filterProperties}})}(t);return r}function t(e,r){for(var t in e)r[t]&&(r[t].keyframes.transform=e[t]);return r}function a(e,r,t){switch(t){case"geometry":case"transform":return"rotateZ"!==r||e[r]?e[r]:e.rotate;case"transform-origin":return f(e[r]);case"-webkit-filter":return c(e[t]);case"boxShadow":return m(e["box-shadow"]);case"backgroundColor":return i(e["background-color"]);case"font":return u(e,r);case"styles":return"color"===r?o(e.color):"borderColor"===r?s(e["border-color"]):l(e,r);default:return!1}}function n(e){for(var r=[],t=0;t<e.length;t++){var a=e[t].declarations.transform,n=function_helpers_1.default.createFilterPropertyGroup(a);a=Object.keys(n).map(function(a){if(n[a]){var i=$.extend(!0,{},e[t]);delete i.declarations.transform,i.declarations[a]=n[a],r.push(i)}})}return r}function i(e){return e}function o(e){return e}function s(e){return e}function l(e,r){return e[function_helpers_1.default.convertJsToCssProperty(r)]}function u(e,r){return e[function_helpers_1.default.convertJsToCssProperty(r)]}function f(e){var r=/\(([^)]+)\)/.exec(e);return r?r[1]:e}function c(e){return e}function m(e){return e}function p(e,r){var t=r*(e/100);return parseInt(t.toFixed())}e.importCss=function(e){var r=parser.parse(e);return r=JSON.parse(JSON.stringify(r,null,"\t")),d(r.rulelist)};var d=function(e){for(var i,o,s,l,u={},f=0;f<e.length;f++){if("style"===e[f].type){if(i=e[f].declarations["custom-metadata"],o=e[f].declarations["transforms-metadata"],i){var c=i.substr(1,i.length-2).replace(/\s(?!(\d+(?=px)))/g,"");s=JSON.parse(c)}if(o){var m=o.substr(1,o.length-2).replace(/\s(?!(\d+(=px)))/g,"");l=JSON.parse(m)}var d=e[f].selector,v=e[f].selector.substr(1).trim();d.startsWith("#")&&main_1.default.animationsBackwardsCompatibility.idsToClasses.push(v);var y=e[f].declarations;u[v]={},u[v].keyframes={},u[v].className=v,u[v].animationsData={},u[v].labels=[],u[v].events={},u[v].belongTo=main_1.default.animationBelongsTo;for(var b=y["animation-delay"].split(/\,/),k=y["animation-direction"].split(/\,/),g=y["animation-duration"].split(/\,/),_=y["animation-iteration-count"].split(/\,/),h=y["animation-timing-function"].split(/\,/),w=y["animation-name"].split(/\,/),C=b.length,x=0;x<C;x++){var D=parseFloat(b[x]),O=parseFloat(g[x]),J=e[f+x+1].keyframes;-1!==w[x].indexOf("transform_")&&(J=n(J));for(var P=0;P<J.length;P++){var F=types_1.default(J[P].declarations);"rotate"===F&&(F="rotateZ");var N=enums_1.default.WidgetGroups[F],S=p(parseFloat(J[P].offset),O)+D,T=a(J[P].declarations,F,N);u[v].keyframes[N]=u[v].keyframes[N]||{},u[v].keyframes[N][F]=u[v].keyframes[N][F]||{},u[v].keyframes[N][F][S]=u[v].keyframes[N][F][S]||{};var q=u[v].keyframes[N][F][S];q.values=[T],q.property=F,q.group=N,q.time={seconds:S};var H=w[x];"transform"===N&&(H=w[x].replace("combined",F)),u[v].animationsData[N]=u[v].animationsData[N]||{},u[v].animationsData[N][F]={direction:k[x],iteration:_[x],timing:h[x],name:H}||{}}}}s&&(u=r(s,u)),l&&(u=t(l,u))}return u}}(importCssHandler||(importCssHandler={})),exports.default=importCssHandler;