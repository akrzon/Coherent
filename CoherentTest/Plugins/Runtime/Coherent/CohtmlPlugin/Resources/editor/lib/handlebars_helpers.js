"use strict";Object.defineProperty(exports,"__esModule",{value:!0});var main_1=require("../scripts/main"),function_helpers_1=require("lib/function_helpers"),Handlebars=require("../bower_components/handlebars/handlebars");Handlebars.registerHelper("debug",function(e){console.log("Current Context"),console.log("===================="),console.log(this),e&&(console.log("Value"),console.log("===================="),console.log(e))}),Handlebars.registerHelper("is_in_scene",function(e,r,t){var n=e.replace("uiresources/",""),a=main_1.default.openFiles[main_1.default.selectedEditor].runtimeEditor.scene;n.startsWith("../")&&(n=n.replace(/\.\.\//g,""));var i=t.inverse,s=t.fn;r="style"===r?"styles":"scripts";for(var l=0;l<a[r].length;l++)if(a[r][l].replace(/\?.*/,"")===n)return s();return i()}),Handlebars.registerHelper("font-enabled",function(e,r,t){for(var n=e.replace("uiresources/","").replace(/\\/g,"/"),a=main_1.default.openFiles[main_1.default.selectedEditor].runtimeEditor.scene,i=0;i<a.fonts.length;i++)if(n===a.fonts[i])return t.fn();return t.inverse()}),Handlebars.registerHelper("each_hash",function(e,r){var t=r.fn,n=r.inverse,a="";if("object"==typeof e)for(var i in e)e.hasOwnProperty(i)&&(a+=t($.extend({_key:i},e[i])));else a=n(this);return a}),Handlebars.registerHelper("select",function(e,r){var t=$("<select />").html(r.fn(this));return t.find('[value="'+e+'"]').attr({selected:"selected"}),t.html()}),Handlebars.registerHelper("radioOption",function(e,r,t){void 0===t&&(t=r);var n=$("<radioOption />").html(t.fn(this));return"boxShadow"===r&&void 0===e?n.find('[value="remove"]').attr({checked:"checked"}):n.find('[value="'+e+'"]').attr({checked:"checked"}),n.html()}),Handlebars.registerHelper("select_units",function(e,r){var t=$("<select />").html(r.fn(this));if(void 0!==e){var n=e.match(/\D+$/);t.find('[value="'+n+'"]').attr({selected:"selected"})}return t.html()}),Handlebars.registerHelper("ifvalue",function(e,r){return r.hash.value===e?r.fn(this):r.inverse(this)}),Handlebars.registerHelper("ifvalueNot",function(e,r){return r.hash.value!==e?r.fn(this):r.inverse(this)}),Handlebars.registerHelper("ifvalues",function(e,r){var t=JSON.parse(r.hash.value),n=t.items.length;if(t.notEqual){for(var a=0;a<n;a++)if(t.items[a]===e){if(t.showHide){var i=$(r.fn(this));return i.addClass("hidden"),i.prop("outerHTML")}return r.inverse(this)}return r.fn(this)}for(var s=0;s<n;s++)if(t.items[s]===e)return r.fn(this);return r.inverse(this)}),Handlebars.registerHelper("option",function(e,r,t){var n=e===t?'selected="selected"':"";return new Handlebars.SafeString('<option value="'+e+'"'+n+">"+r+"</option>")}),Handlebars.registerHelper("format_value",function(e,r){if(e){var t=e.split(/[^a-zA-Z%]+/);if(t){if("px"===t[1]||"deg"===t[1]||"rad"===t[1]||"%"===t[1])return 1;var n=main_1.default.openFiles[main_1.default.selectedEditor].runtimeEditor.getFormat();return 1/Math.pow(10,n)}}}),Handlebars.registerHelper("format_name",function(e,r){if(e.length>20){var t=e.length;return"..."+(e=e.substring(t-20,t))}return e}),Handlebars.registerHelper("is_component",function(e,r){return e.name.endsWith(".component")?'<span class="fa fa-remove fa-right-small delete-component" data-url="'+e.url+'" data-link="'+e.name+'"></span>':""}),Handlebars.registerHelper("is_widget",function(e,r){return e.name.endsWith(".component")?"":'<span class="fa fa-sign-out fa-right-small convert-widget" data-url="'+e.url+'" data-link="'+e.name+'"></span>'}),Handlebars.registerHelper("format_name_background_url",function(e,r){return function_helpers_1.default.cleanBackgroundUrls(e)}),Handlebars.registerHelper("number_only",function(e,r){main_1.default.openFiles[main_1.default.selectedEditor].runtimeEditor.getFormat();if(void 0!==(e=e.toString())){if("auto"===e)return"0";var t=/[^a-zA-Z%]+/,n=e.match(t);if(null!==n){var a=parseFloat(n[0]),i=e.split(t)[1];return"px"===i||"deg"===i||"rad"===i?parseInt(a.toString()):a}return n}}),Handlebars.registerHelper("rad_to_deg",function(e,r){if(void 0!==e){if(void 0!==e){var t=/[^a-zA-Z%]+/,n=e.match(t);return"deg"!==e.split(t)[1]&&(n*=180/Math.PI),parseInt(n)}}}),Handlebars.registerHelper("ifCond",function(e,r,t,n){var a=!1;switch(r){case"===":a=e===t;break;case"!==":a=e!==t;break;case"<":a=e<t;break;case"<=":a=e<=t;break;case">":a=e>t;break;case">=":a=e>=t;break;case"||":a=e||t;break;case"&&":a=e&&t}return a?n.fn(this):n.inverse(this)}),Handlebars.registerHelper("CompileBackground",function(e,r){var t=!1;return"image"!==e.type&&"responsiveImage"!==e.type&&void 0===e.styles.webkitMaskImage&&void 0===e.background&&void 0===e.styles.backgroundImage||(t=!0),t?r.fn(this):r.inverse(this)}),Handlebars.registerHelper("hideHummingbird",function(e,r){if("Hummingbird"!==e)return r.fn(this)}),exports.default=Handlebars;