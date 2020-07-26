"use strict";var __awaiter=this&&this.__awaiter||function(e,t,n,o){return new(n||(n=Promise))(function(i,r){function a(e){try{s(o.next(e))}catch(e){r(e)}}function l(e){try{s(o.throw(e))}catch(e){r(e)}}function s(e){e.done?i(e.value):new n(function(t){t(e.value)}).then(a,l)}s((o=o.apply(e,t||[])).next())})},__generator=this&&this.__generator||function(e,t){function n(e){return function(t){return o([e,t])}}function o(n){if(i)throw new TypeError("Generator is already executing.");for(;s;)try{if(i=1,r&&(a=r[2&n[0]?"return":n[0]?"throw":"next"])&&!(a=a.call(r,n[1])).done)return a;switch(r=0,a&&(n=[0,a.value]),n[0]){case 0:case 1:a=n;break;case 4:return s.label++,{value:n[1],done:!1};case 5:s.label++,r=n[1],n=[0];continue;case 7:n=s.ops.pop(),s.trys.pop();continue;default:if(a=s.trys,!(a=a.length>0&&a[a.length-1])&&(6===n[0]||2===n[0])){s=0;continue}if(3===n[0]&&(!a||n[1]>a[0]&&n[1]<a[3])){s.label=n[1];break}if(6===n[0]&&s.label<a[1]){s.label=a[1],a=n;break}if(a&&s.label<a[2]){s.label=a[2],s.ops.push(n);break}a[2]&&s.ops.pop(),s.trys.pop();continue}n=t.call(e,s)}catch(e){n=[6,e],r=0}finally{i=a=0}if(5&n[0])throw n[1];return{value:n[0]?n[1]:void 0,done:!0}}var i,r,a,l,s={label:0,sent:function(){if(1&a[0])throw a[1];return a[1]},trys:[],ops:[]};return l={next:n(0),throw:n(1),return:n(2)},"function"==typeof Symbol&&(l[Symbol.iterator]=function(){return this}),l};Object.defineProperty(exports,"__esModule",{value:!0});var enums_1=require("lib/enums"),units_conversion_1=require("../../scripts/helpers/units_conversion"),main_1=require("../../scripts/main"),Component=function(){function e(){this.components={},this.state={opened:[]}}return e.prototype.create=function(e,t){this.components[e]=t;var n=main_1.default.openFiles[main_1.default.selectedEditor].runtimeEditor;return n._sceneActionState.createComponent=!0,n.saveUndoRedo(null,null,null,{componentName:e},null),n.exportScene(),this},e.prototype.isComponentOpened=function(e){for(var t=0;t<this.state.opened.length;t++){var n=this.state.opened[t];if(main_1.default.openFiles[n].tab.filename===e)return this.state.opened[t]}return!1},e.prototype.remove=function(e){var t=this.isComponentOpened(e);t&&main_1.default.forceClose(t);var n=main_1.default.openFiles[main_1.default.selectedEditor].runtimeEditor;n._sceneActionState.deleteComponent=!0;var o=n.getRedoUndoPrimaryState(),i={name:e,json:this.components[e]},r=$('[data-widgetkit="'+e+'"]'),a=r.length;"new action"===o&&(n._undoCreationStepsLength=a+1),n.saveUndoRedo(null,null,null,i,null),delete this.components[e];for(var l=[],s=0;s<a;s++)l.push(r[s].getAttribute("id"));return n.removeWidgets(l),this},e.prototype.registerComponents=function(){var e=main_1.default.environmentProperties,t="\n"+e.REGISTER_COMPONENTS_MARK_START;t+="\n<script>";var n=0;for(var o in this.components)t+="\nvar component"+n+" = getComponentData('"+o+"');\n",t+="engine.registerComponent('"+o+"', {\n   template: component"+n+".template,\n   create: function () {\n      return this.appendChild(component"+n+".script);\n   }\n})\n",n++;return t+="function getComponentData(componentName) {\n   var el = document.querySelectorAll('[data-load-component-id=\"' + componentName + '\"]');\n   var html = document.createElement('html');   html.innerHTML = el[0].innerHTML;\n   var localEvents = html.getElementsByClassName('local-events')[0];\n   var script = document.createElement('script');\n   script.innerHTML = localEvents.innerHTML;\n   var component = html.querySelectorAll('[data-widgetkit=\"' + componentName + '\"]')[0];\n   return {\n       template: component,\n       script: script\n   };\n }\n",t+="\n<\/script>\n",t+=e.REGISTER_COMPONENTS_MARK_END+"\n"},e.prototype.replaceScriptTags=function(e,t){void 0===t&&(t=!1);return t?e.replace(/<x-script/g,"<script").replace(/<\/x-script/g,"</script"):e.replace(/<script/g,"<x-script").replace(/<\/script/g,"</x-script")},e.prototype.buildComponentExportHTML=function(){return __awaiter(this,void 0,void 0,function(){var e,t,n,o,i,r,a,l,s,c=this;return __generator(this,function(p){switch(p.label){case 0:e=$.Deferred(),t=main_1.default.environmentProperties,n=main_1.default.openFiles[main_1.default.selectedEditor],o="",i=[];for(r in this.components)i.push(r);a=0,p.label=1;case 1:return a<i.length?(l=i[a],o+='\n<script type="text/html" data-load-component-id="'+l+'">\n'+t.COMPONENTS_MARK_START+"\n",s=o,[4,n.runtimeEditor.runtimeLoad(this.components[l],{widgetSave:!0}).then(function(e){var n=main_1.default.rebuildUserHTML(e,"",!0),o=main_1.default.cleanupHtmlExport(n);return(o=c.replaceScriptTags(o))+"\n"+t.COMPONENTS_MARK_END+"\n\n<\/script>\n"}).catch(function(e){console.log(e.message)})]):[3,4];case 2:o=s+p.sent(),p.label=3;case 3:return a++,[3,1];case 4:return[2,e.resolve(o)]}})})},e.prototype.cleanupCommentMarks=function(e){var t=main_1.default.environmentProperties;return e.replace(t.COMPONENTS_MARK_START,"").replace(t.COMPONENTS_MARK_END,"")},e.prototype.load=function(e){var t=/\/\* Editor Components Start \*\/([\s\S]*?)\/\* Editor Components End \*\//gm;if(e.match(t)){var n=e.match(t);if(n.length>0){for(var o={},i=0;i<n.length;i++){n[i]=this.replaceScriptTags(n[i],!0),n[i]=this.cleanupCommentMarks(n[i]);var r=main_1.default.buildWidgetSceneObjFromHtml(n[i]);o[r.widgets[0].widgetkit]=JSON.stringify(r)}this.components=o}}},e.prototype.open=function(e,t){var n=this,o=main_1.default.selectedEditor;return main_1.default.openAsset({name:t,content:e}),$("body").off("__openComponentComplete"),$("body").on("__openComponentComplete",function(){var e=main_1.default.selectedEditor;-1===n.state.opened.indexOf(e)&&(main_1.default.openedTabsTypes.components.push(e),n.state.opened.push(e)),main_1.default.openFiles[main_1.default.selectedEditor].tab.tabWidgetState.instanceOf=o,document.body.dispatchEvent(new Event("__componentInstanceSet"))}),this},e.prototype.clearOpenedData=function(e){var t=this.state.opened.indexOf(e);return t>-1&&(main_1.default.openedTabsTypes.components.splice(t,1),this.state.opened.splice(t,1)),this},e.prototype.save=function(e,t){this.components[e]=t,main_1.default.EXPORTING_COMPONENT&&(main_1.default.EXPORTING_COMPONENT=!1),main_1.default.tabEdited(!1)},e.prototype._insertToTheScene=function(e,t){var n=e.getAttribute("data-url"),o=e.getAttribute("data-widget-name");""!==n?this._fetchWidgetFromFileAndInsertToTheScene(n,t):this._insertWidgetComponentToTheScene(o,t)},e.prototype._fetchWidgetFromFileAndInsertToTheScene=function(e,t){var n=this,o=main_1.default.openFiles[main_1.default.selectedEditor].runtimeEditor;main_1.default.globalEditorInfo.backend===enums_1.default.Backends.Debug||main_1.default.globalEditorInfo.backend===enums_1.default.Backends.Website?e+="!text":e=o.buildWidgetUrl(e),System.import(e).then(function(e){var o=n._getDroppedOffset(t),i="left: "+o.x+"vw; ",r=" top: "+o.y+"vh; ",a=/<body>([\s\S]*)<\/body>/.exec(e.valueOf())[0],l=""+/<([\s\S]*)<\/head>/.exec(e.valueOf())[0]+(a=(a=a.replace(a.match(/(top:).*?;/)[0],r)).replace(a.match(/(left:).*?;/)[0],i))+"</html>",s=main_1.default.selectedEditor,c=main_1.default.openFiles[main_1.default.selectedEditor].tab.filename;main_1.default.openFiles[main_1.default.selectedEditor].tab.tabWidgetState.importedWidget=!0,main_1.default.handleFileContent(l,c,s,!1,!0)})},e.prototype._getDroppedOffset=function(e){var t=main_1.default.openFiles[main_1.default.selectedEditor].runtimeEditor._getSceneOffset(e);return{x:units_conversion_1.default.convertPixelToVw(t.x),y:units_conversion_1.default.convertPixelToVh(t.y)}},e.prototype._insertWidgetComponentToTheScene=function(e,t){var n=main_1.default.openFiles[main_1.default.selectedEditor],o=this._getDroppedOffset(t),i=JSON.parse(n.components.components[e]);i.widgets[0].geometry.top=o.y+"vh",i.widgets[0].geometry.left=o.x+"vw";var r=main_1.default.selectedEditor,a=n.tab.filename;n.tab.tabWidgetState.importedWidget=!0,main_1.default.handleFileContent(JSON.stringify(i),a,r,!1,!0)},e}();exports.default=Component;