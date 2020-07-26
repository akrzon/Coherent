"use strict";Object.defineProperty(exports,"__esModule",{value:!0});var enums_1=require("../enums"),function_helpers_1=require("../function_helpers"),main_1=require("../../scripts/main"),tooltipHbs=require("lib/animations/hbs/tooltip_options.hbs!text"),MAX_ZOOM=4,MIN_ZOOM=1,DEFAULT_ZOOM=2.5,ZOOM_STEP=.1,PIN_WIDTH=10,LEFT_PANEL_SIZE=270,ADD_TIME_OFFSET=50,APPEND_MORE_TIME=10,TIMELINE_LEFT_OFFSET=0,GT_PINOFFSET_FIX=.5,refreshInterval=null,documentWidth,leftBarOffset,draggedElement,Timeline=function(){function e(e){this.$timelineEl=$(".timeline"),this.$timelineWrap=$(".timeline-wrap"),this.$animTimeEl=$(".animation-timeline"),this.$pin=$("#timeline-pin"),this.$ruler=$("#timeline-ruler"),this.$timelineInput=$("#timeline-input"),this.$infoWidgetsSection=$(".info-stack"),this.timelineWidth=2e3,this.timelineZoom=DEFAULT_ZOOM,this.originalRulerWidth=2e3,this.pinCurrentSeconds=0,this.currentSeconds=0,this.oldPinheadSeconds=0,this.pinHalfWidth=4,this.runtimeEditor=e,this.templateWidgetLine=document.getElementById("widget-line-html"),this.templateTimelineInfo=document.getElementById("timeline-info"),this.dragFlag=!1,this.animationSearchValue="",this.timelineInputHandler()}return e.prototype.create=function(){this.$timelineEl.off("mousewheel"),this.selectKeyframeHandlers(),this.draggingPointsHandlers(),this.createTimeline(),this.zoomHandler(),this.timelineScrollHandler()},e.prototype.getPinTime=function(){return{offset:this.$pin[0].offsetLeft,seconds:this.pinCurrentSeconds}},e.prototype.zoomHandler=function(){var e=this;this.$timelineEl.off("mousewheel"),this.$timelineEl.on("mousewheel",function(t){t.preventDefault();var i=t.delta||t.originalEvent.wheelDelta,n=i?i<0:t.originalEvent.deltaY>0,a=e.$pin[0].offsetLeft;if(!(!n&&e.timelineZoom>=MAX_ZOOM||n&&e.timelineZoom<=MIN_ZOOM)){e.zoom(n),e.createTimeline();var o=e.$pin[0].offsetLeft-a;e.$pin[0].offsetLeft>0&&e.rulerScrollRight(o)}})},e.prototype.zoom=function(e){var t=this,i=e?1:0,n=ZOOM_STEP*+!i-ZOOM_STEP*i,a=(this.timelineZoom+n)/this.timelineZoom;this.timelineZoom+=function_helpers_1.default.toFixed(n,2),$(".dragging-point").each(function(){var e=$(this)[0].offsetLeft*a;main_1.default.globalEditorInfo.backend!==enums_1.default.Backends.Debug&&main_1.default.globalEditorInfo.backend!==enums_1.default.Backends.Website&&main_1.default.globalEditorInfo.backend!==enums_1.default.Backends["Standalone-2"]&&(e+=GT_PINOFFSET_FIX),t.renderPoint(e,$(this))})},e.prototype.extendTimeline=function(){this.timelineWidth=this.originalRulerWidth*this.timelineZoom,this.setTimelineWidth(this.timelineWidth)},e.prototype.setTimelineWidth=function(e){this.$ruler.attr("width",e),this.$timelineEl[0].style.width=e+"px"},e.prototype.createTimeline=function(){this.extendTimeline();var e=this.$ruler[0].getContext("2d");this.timelinePositions({render:e})},e.prototype.createWidgetLines=function(){var e=function_helpers_1.default.getFromTimeline(".keyframes-line")[0].getContext("2d");e.beginPath(),this.timelinePositions({render:e})},e.prototype.timelinePositions=function(e,t){for(var i=0,n=function_helpers_1.default.toFixed(this.timelineWidth,2),a=0;a<n;a+=10*this.timelineZoom,i+=100)e.render&&this.renderTimeline(e.render,a,i),e.calcTimePosition&&this.calcTimePosition(e.calcTimePosition,a,10,i,100,t);return i},e.prototype.renderTimeline=function(e,t,i){e.font="10px Helvetica, sans-serif",e.fillStyle="#fff",i%1e3==0?(e.beginPath(),e.moveTo(t,0),e.lineTo(t,16),e.strokeStyle="#fff",e.stroke(),e.fillText(i,t+3,10)):this.timelineZoom>1&&i%500==0?(e.beginPath(),e.moveTo(t,0),e.lineTo(t,8),e.strokeStyle="#fff",e.stroke(),e.fillText(i,t+3,10)):this.timelineZoom>2&&i%100==0?(e.beginPath(),e.moveTo(t,0),e.lineTo(t,5),e.strokeStyle="#fff",e.stroke()):this.timelineZoom>3&&i%50==0&&(e.beginPath(),e.moveTo(t,0),e.lineTo(t,5),e.strokeStyle="#fff",e.stroke())},e.prototype.renderPoint=function(e,t){e<0&&(e=-4),t.css("left",e)},e.prototype.getKeyframeWidgetData=function(e){var t=e[0].attributes["data-animation-class"].value,i=e[0].attributes["data-current-time"].value,n=e[0].attributes["data-keyframe-widget-id"].value,a=e[0].attributes["data-keyframe-group"].value,o=e[0].attributes["data-keyframe-property"].value;return{className:t,time:i,id:n,group:a,prop:o,value:this.runtimeEditor.scene.animationClasses[t].keyframes[a][o][i].values[0]}},e.prototype.selectKeyframe=function(e){var t=this.getKeyframeWidgetData(e),i=this.runtimeEditor.currentElementsSelection;0!==i.length&&i[0]===t.id||this.runtimeEditor.selectJstreeItem(t.id),function_helpers_1.default.getFromTimeline("div[data-keyframe-widget-id]").removeClass("keyframe-pressed"),e.addClass("keyframe-pressed");var n=e.attr("data-keyframe-widget-id");this.toggleElementTimeline($("#"+n),!0),$(".breadcrumb").html('<span class="keyframe-info-text"><b>Animated element: </b></span>'+t.id+'<span class="keyframe-info-text">&nbsp&nbsp<b> property: </b></span> '+t.prop+'<span class="keyframe-info-text">&nbsp&nbsp<b> value: </b></span>'+t.time)},e.prototype.unselectAllKeyfames=function(){function_helpers_1.default.getFromTimeline("div[data-keyframe-widget-id]").removeClass("keyframe-pressed"),this.runtimeEditor.selectedKeyframes.length=0},e.prototype.unhighlightAllTracks=function(){function_helpers_1.default.getFromTimeline("div[data-timeline-info-widget-id] > div").removeClass("element-track-selected"),function_helpers_1.default.getFromTimeline("div[data-timeline-info-widget-id] > div > .info-widget-name").removeClass("element-track-selected"),function_helpers_1.default.getFromTimeline("div[data-widget-id] > .keyframe-line").removeClass("element-track-selected"),function_helpers_1.default.getFromTimeline("div[data-timeline-info-widget-id] > .info-class-name").removeClass("class-track-selected"),function_helpers_1.default.getFromTimeline("div[data-widget-id] > .keyframe-line-class-name").removeClass("class-track-selected"),function_helpers_1.default.getFromTimeline("div[data-timeline-info-widget-id] > .info-property-name").removeClass("track-selected"),function_helpers_1.default.getFromTimeline("div[data-widget-id] > div > .selectable-track").removeClass("track-selected"),function_helpers_1.default.getFromTimeline("div[data-timeline-info-widget-id] > div > .animation-class-name-input").removeClass("input-track-selected")},e.prototype.selectKeyframeHandlers=function(){var e=this;function_helpers_1.default.getFromTimeline(".dragging-point").off("mousedown"),function_helpers_1.default.getFromTimeline(".dragging-point").on("mousedown",function(t){e.runtimeEditor.blurOutTextInputs(),"timeline-pin"!==$(this)[0].id&&(e.selectKeyframe($(this)),e.runtimeEditor.selectedKeyframes[0]=$(this))}),$("html").off("click"),$("html").on("click",function(t){e.dragFlag&&(e.dragFlag=!1)})},e.prototype.toggleElementTimeline=function(e,t){var i=e.attr("id"),n=document.getElementById("anim-option-"+i);t?(function_helpers_1.default.getFromTimeline('div[data-timeline-info-widget-id="'+i+'"] > div').addClass("element-track-selected"),function_helpers_1.default.getFromTimeline('div[data-timeline-info-widget-id="'+i+'"] > div > .info-widget-name').addClass("element-track-selected"),function_helpers_1.default.getFromTimeline('div[data-widget-id="'+i+'"] > .keyframe-line').addClass("element-track-selected"),function_helpers_1.default.getFromTimeline('div[data-timeline-info-widget-id="'+i+'"] > .info-class-name').addClass("class-track-selected"),function_helpers_1.default.getFromTimeline('div[data-widget-id="'+i+'"] > .keyframe-line-class-name').addClass("class-track-selected"),function_helpers_1.default.getFromTimeline('div[data-timeline-info-widget-id="'+i+'"] > .info-property-name').addClass("track-selected"),function_helpers_1.default.getFromTimeline('div[data-widget-id="'+i+'"] > div > .selectable-track').addClass("track-selected"),function_helpers_1.default.getFromTimeline('div[data-timeline-info-widget-id="'+i+'"] > div > .animation-class-name-input').addClass("input-track-selected"),null!==n&&n.scrollIntoView({block:"start",behavior:"smooth"})):(function_helpers_1.default.getFromTimeline('div[data-timeline-info-widget-id="'+i+'"] > div').removeClass("element-track-selected"),function_helpers_1.default.getFromTimeline('div[data-timeline-info-widget-id="'+i+'"] > div > .info-widget-name').removeClass("element-track-selected"),function_helpers_1.default.getFromTimeline('div[data-widget-id="'+i+'"] > .keyframe-line').removeClass("element-track-selected"),function_helpers_1.default.getFromTimeline('div[data-timeline-info-widget-id="'+i+'"] > .info-class-name').removeClass("class-track-selected"),function_helpers_1.default.getFromTimeline('div[data-widget-id="'+i+'"] > .keyframe-line-class-name').removeClass("class-track-selected"),function_helpers_1.default.getFromTimeline('div[data-timeline-info-widget-id="'+i+'"] > .info-property-name').removeClass("track-selected"),function_helpers_1.default.getFromTimeline('div[data-widget-id="'+i+'"] > div > .selectable-track').removeClass("track-selected"),function_helpers_1.default.getFromTimeline('div[data-timeline-info-widget-id="'+i+'"] > div > .animation-class-name-input').removeClass("input-track-selected"))},e.prototype.draggingPointsHandlers=function(){var e,t=this,i=[];function_helpers_1.default.getFromTimeline(".dragging-point").kendoDraggable({group:"keyframesGroup",hint:function(e){var t=(draggedElement=e).attr("data-current-time"),n=draggedElement.attr("data-keyframe-group"),a=draggedElement.attr("data-keyframe-property"),o=draggedElement.attr("data-animation-class");return i=$('[data-current-time="'+t+'"][data-keyframe-group="'+n+'"][data-keyframe-property="'+a+'"][data-animation-class="'+o+'"]'),e.clone().addClass("ob-clone")},drag:function(e){var i=e.clientX;"timeline-pin"!==draggedElement[0].id&&(t.runtimeEditor.selectedKeyframes[0]=draggedElement,t.dragFlag=!0),i>documentWidth-60?null===refreshInterval&&(refreshInterval=setInterval(t.rulerScrollRight.bind(t),5)):i<leftBarOffset.left?null===refreshInterval&&(refreshInterval=setInterval(t.rulerScrollLeft.bind(t),5)):(clearInterval(refreshInterval),refreshInterval=null);var n=t.$timelineWrap.scrollLeft(),a=parseFloat($(".ob-clone")[0].style.left)-leftBarOffset.left+n;"timeline-pin"===draggedElement[0].id&&(t.moveTimePoint(draggedElement,a),t.setTimelineInput(t.currentSeconds))},dragstart:function(i){t.runtimeEditor._sceneActionState.primaryAction="new action",documentWidth=$(document).width(),leftBarOffset=$("#horizontal-timeline-splitter .k-splitbar").offset(),draggedElement.addClass("ob-hide"),$("mask.select-corners").hide(),$(".transform-origin-point").hide(),e=t.runtimeEditor.currentElementsSelection,t.runtimeEditor._sceneActionState.draggingTimelinePin=!0},axis:"x",container:t.$timelineWrap,dragend:function(n){var a=t.$timelineWrap.scrollLeft(),o=parseFloat($(".ob-clone")[0].style.left)-leftBarOffset.left+a;if(clearInterval(refreshInterval),refreshInterval=null,t.runtimeEditor._sceneActionState.draggingTimelinePin=!1,"timeline-pin"!==draggedElement[0].id){t.runtimeEditor._undoCreationStepsLength=i.length;for(var r=0;r<i.length;r++)t.moveTimePoint($(i[r]),o);t.selectKeyframe(draggedElement)}else t.moveTimePoint(draggedElement,o),t.setTimelineInput(t.currentSeconds);$("mask.select-corners").show(),$(".transform-origin-point").show(),e.length>0&&t.runtimeEditor.highlightSelectedEl(null,e),t.runtimeEditor.exportScene()}}),$("body").kendoDropTarget({group:"keyframesGroup",drop:function(e){var t=$(".ob-clone");t.css("visibility","hidden");var i=t.offset();$(e.draggable.currentTarget).removeClass("ob-hide").offset(i)}}),this.$animTimeEl.off("click"),this.$animTimeEl.on("click",function(e){t.runtimeEditor.blurOutTextInputs(),"timeline-ruler"===e.target.id&&(t.setPinheadPosition(e.offsetX),t.setTimelineInput(t.currentSeconds))})},e.prototype._getKeyframeOffsets=function(){for(var e=function_helpers_1.default.getFromTimeline(".keyframe"),t=[],i=0;i<e.length;i++)t.push(e[i].offsetLeft);return t=t.sort(function(e,t){return e-t})},e.prototype._getTimelinePositions=function(){var e=function_helpers_1.default.getFromTimeline(".dragging-point")[0].offsetLeft,t=this._getKeyframeOffsets();return{pin:e,keyframes:function_helpers_1.default.removeDuplicates(t)}},e.prototype.setToNextKeyframe=function(){var e=this._getTimelinePositions();if(e.keyframes.length>0){var t=function_helpers_1.default.biggerClosest(e.keyframes,e.pin),i=this.convertOffsetXToTime(t);this.setTimelineInput(i),this.setPinheadPosition(t)}},e.prototype.setToPreviousKeyframe=function(){var e=this._getTimelinePositions();if(e.keyframes.length>0){var t=function_helpers_1.default.smallerClosest(e.keyframes,e.pin),i=this.convertOffsetXToTime(t);this.setTimelineInput(i),this.setPinheadPosition(t)}},e.prototype.setToFirstKeyframe=function(){var e=this._getKeyframeOffsets()[0];if(e){var t=this.convertOffsetXToTime(e);this.setTimelineInput(t),this.setPinheadPosition(e)}},e.prototype.setToLastKeyframe=function(){var e=this._getKeyframeOffsets(),t=e[e.length-1];if(t){var i=this.convertOffsetXToTime(t);this.setTimelineInput(i),this.setPinheadPosition(t)}},e.prototype.revertPinheadPosition=function(){this.setTimelineInput(this.oldPinheadSeconds),this.setPinheadPosition(0,this.oldPinheadSeconds)},e.prototype.convertTimeToOffsetX=function(e){return e/10*this.timelineZoom-this.pinHalfWidth},e.prototype.convertOffsetXToTime=function(e){var t=10*e/this.timelineZoom-this.pinHalfWidth;return this.formatTimelineInputValue(t)},e.prototype.getLastKeyframeTime=function(){var e=null;return function_helpers_1.default.getFromTimeline(".keyframe").each(function(){var t=parseInt($(this).attr("data-current-time"));(null===e||t>e)&&(e=t)}),e||!1},e.prototype.doTimerTimeout=function(e,t,i,n,a){function o(){if(d++===s&&a===enums_1.default.animationPreviewType.endlessPreview)n(s,d);else{i(s,d);var e=(new Date).getTime()-m-d*l;r.runtimeEditor.iframe?window.setTimeout(o,l-e):n(s,d)}}var r=this,s=e/100*(t/10),l=e/s,d=0,m=(new Date).getTime();window.setTimeout(o,l)},e.prototype.doTimerAnimationFrame=function(e,t,i,n){function a(l){s||(s=l);var d=l-s,m=e/d*(r/o.timelineZoom);t(m),(d<e||n===enums_1.default.animationPreviewType.endlessPreview)&&o.runtimeEditor.iframe?(requestAnimationFrame(a),o.setTimelineInput(d)):i()}var o=this,r=o.timelineZoom,s=null;requestAnimationFrame(a)},e.prototype.animatePinhead=function(e,t){var i=this,n=this.convertTimeToOffsetX(e),a=0,o=function_helpers_1.default.getFromTimeline("#timeline-pin");this.doTimerAnimationFrame(e,function(e){a=n/e,o.css("left",a)},function(){i.revertPinheadPosition()},t)},e.prototype.setPinheadPosition=function(e,t){void 0!==t&&(this.oldPinheadSeconds=this.currentSeconds,this.currentSeconds=t,e=this.convertTimeToOffsetX(t)),this.runtimeEditor._sceneActionState.draggingTimelinePin=!0,this.moveTimePoint(this.$pin,e),this.runtimeEditor._sceneActionState.draggingTimelinePin=!1,this.runtimeEditor.currentElementsSelection.length>0&&!main_1.default.EXPORTING_COMPONENT&&!main_1.default.EXPORTING_WIDGET&&this.runtimeEditor.highlightSelectedEl(null,this.runtimeEditor.currentElementsSelection)},e.prototype.moveTimePoint=function(e,t){var i=parseFloat(e.attr("data-current-time"))||0;this.timelinePositions({calcTimePosition:t},e),"timeline-pin"!==e[0].id?this.runtimeEditor.Keyframes.onKeyframeChange(e,i,this.currentSeconds):this.runtimeEditor.Keyframes.TimelineScrub.renderKeyframesInTime(i,this.currentSeconds),e.attr("data-current-time",this.currentSeconds)},e.prototype.timelineScrollHandler=function(){var e=this;this.$timelineWrap.scroll(function(){+(100*this.scrollLeft/this.scrollWidth/(1-this.clientWidth/this.scrollWidth))>90&&e.addMoreTime()})},e.prototype.setTimelineInput=function(e){function t(e){return(e<10?"0":"")+e}var i=e%1e3,n=(e=(e-i)/1e3)%60,a=t((e=(e-n)/60)%60)+":"+t(n)+":"+("000"+i).substr(-3);this.$timelineInput.val(a)},e.prototype.formatTimelineInputValue=function(e){return(e=e<0?0:e)%100>50?100*Math.ceil(e/100):100*Math.floor(e/100)},e.prototype.timelineInputHandler=function(){var e=this;this.$timelineInput=function_helpers_1.default.getFromTimeline("#timeline-input"),this.$timelineInput.val("00:00:000"),this.$timelineInput.off("blur keyup"),this.$timelineInput.on("blur keyup",function(t){if(t.preventDefault(),t.keyCode!==enums_1.default.Keys.left&&t.keyCode!==enums_1.default.Keys.right&&t.keyCode!==enums_1.default.Keys.ctrl&&t.keyCode!==enums_1.default.Keys.shift&&t.keyCode!==enums_1.default.Keys.up&&t.keyCode!==enums_1.default.Keys.down&&t.keyCode===enums_1.default.Keys.enter){var i,n,a,o=$(this),r=o.val().split(":");1===r.length?(i=0,n=0,r[0]=""===r[0].trim()?0:r[0],a=parseInt(r[0])):2===r.length?(i=0,n=parseInt(r[0]),a=parseInt(r[1])):(i=parseInt(r[0]),n=parseInt(r[1]),a=parseInt(r[2]));var s=a+1e3*n+6e4*i;s=s>3599999?3599999:s,s=e.formatTimelineInputValue(s),e.timelineWidth=e.timelineWidth<s?s:e.timelineWidth,e.setPinheadPosition(null,s),e.setTimelineInput(s),o.blur()}})},e.prototype.rulerScrollLeft=function(){var e=this.$timelineWrap.scrollLeft();this.$timelineWrap.scrollLeft(e-2)},e.prototype.rulerScrollRight=function(e){var t=e||2,i=this.$timelineWrap.scrollLeft();this.$timelineWrap.scrollLeft(i+t)},e.prototype.addMoreTime=function(){this.$timelineEl.width("+="+APPEND_MORE_TIME),this.originalRulerWidth=this.$timelineEl.width(),this.createTimeline()},e.prototype.calcTimePosition=function(e,t,i,n,a,o){e-=TIMELINE_LEFT_OFFSET;var r=i*this.timelineZoom,s=t-r,l=n-a;(e>=s&&e<=s+r||e>=s-r/2&&e<=s)&&this.setPointSeconds(l,s,o)},e.prototype.setPointSeconds=function(e,t,i){this.currentSeconds=e,"timeline-pin"===i[0].id&&(this.pinCurrentSeconds=this.currentSeconds),this.renderPoint(t-this.pinHalfWidth,i)},e.prototype.deleteKeyframe=function(e){var t=function_helpers_1.default.getFromTimeline(".widget-line."+e.className+'[data-property-type="'+e.prop+'"]'),i=this.runtimeEditor.scene,n=i.animations[e.id][e.className],a=n.keyframes[e.group];if(a){var o=a[e.prop];if(delete o[e.time],t.find('[data-current-time="'+e.time+'"]').remove(),$.isEmptyObject(o)&&(delete n.animationsData[e.group][e.prop],delete n.keyframes[e.group][e.prop],o=null,t.remove(),function_helpers_1.default.getFromTimeline(".info-property-name."+e.className+'[data-timeline-info-property-name="'+e.prop+'"]').remove()),$.isEmptyObject(n.keyframes[e.group])&&(delete n.keyframes[e.group],delete n.animationsData[e.group]),$.isEmptyObject(n.keyframes))for(var r in i.animations)i.animations[r][e.className]&&delete i.animations[r][e.className]}var s=this.runtimeEditor.getRedoUndoPrimaryState(),l={seconds:e.time,value:e.value};this.runtimeEditor._sceneActionState.deleteKeyframe=!0,this.runtimeEditor.createUndoRedoCommand(s,e.id,e.group,e.group,e.prop,l),this.runtimeEditor.exportScene(),function_helpers_1.default.getFromTimeline(".info-widgets").getNiceScroll().resize()},e.prototype.deleteSelectedKeyframes=function(){for(var e=this.runtimeEditor.selectedKeyframes.length,t=0;t<e;t++){var i=this.runtimeEditor.selectedKeyframes[t],n=this.getKeyframeWidgetData(i),a=function_helpers_1.default.getFromTimeline('.keyframe[data-animation-class="'+n.className+'"][data-keyframe-property="'+n.prop+'"][data-current-time="'+n.time+'"]').length;this.runtimeEditor._undoCreationStepsLength=a;for(var o in this.runtimeEditor.scene.animations)this.runtimeEditor.scene.animations[o][n.className]&&(n.id=o,this.deleteKeyframe(n))}this.runtimeEditor.selectedKeyframes.length=0},e.prototype.deleteWidget=function(e){delete this.runtimeEditor.scene.animations[e];var t=function_helpers_1.default.getFromTimeline('[data-timeline-info-widget-id="'+e+'"]'),i=function_helpers_1.default.getFromTimeline('.widgets-keyframes [data-widget-id="'+e+'"]');$(".k-animation-container").has('[kendotooltipid="'+e+'"]').remove(),t.remove(),i.remove()},e.prototype.setInputClassName=function(e,t,i){var n=!1;!e&&function_helpers_1.default.getFromTimeline('.animation-class-name-input[data-old-animation-class="'+i+'"]').length>0?function_helpers_1.default.getFromTimeline('.animation-class-name-input[data-old-animation-class="'+i+'"]').val(t):(function_helpers_1.default.getFromTimeline('[data-timeline-info-widget-id="'+e+'"] .animation-class-name-input').val(t),n=!0),this.setOldAnimationClass(e,t,i,n)},e.prototype.removeClassNameFromDOM=function(e,t){t&&""!==t&&(function_helpers_1.default.getFromTimeline('[data-timeline-info-widget-id="'+e+'"] .info-property-name.'+t).remove(),function_helpers_1.default.getFromTimeline('[data-widget-id="'+e+'"] .widget-line.'+t).remove()),this.runtimeEditor.scene.animations[e]&&"new action"===this.runtimeEditor.getRedoUndoPrimaryState()||!main_1.default.preferences.timeline.filterTimelineWidgets||(function_helpers_1.default.getFromTimeline('[data-timeline-info-widget-id="'+e+'"]').remove(),function_helpers_1.default.getFromTimeline('.widget-line.widget-name-line[data-widget-id="'+e+'"]').remove())},e.prototype.setOldAnimationClass=function(e,t,i,n){!i||n?(function_helpers_1.default.getFromTimeline('[data-timeline-info-widget-id="'+e+'"] [data-old-animation-class]').attr("data-old-animation-class",t),function_helpers_1.default.getFromTimeline('[data-tooltip-change-class-id="'+e+'"] [data-old-animation-class]').attr("data-old-animation-class",t),function_helpers_1.default.getFromTimeline(".k-animation-container").has('[kendotooltipid="'+e+'"]:not([data-tooltip-change-class-id])').remove()):function_helpers_1.default.getFromTimeline('[data-old-animation-class="'+i+'"]').attr("data-old-animation-class",t),this.runtimeEditor.exportScene()},e.prototype.setNewAnimationClass=function(e,t,i){function_helpers_1.default.getFromTimeline("[data-timeline-info-widget-id] ."+i).addClass(t).removeClass(i),function_helpers_1.default.getFromTimeline("[data-widget-id] ."+i).addClass(t).removeClass(i),function_helpers_1.default.getFromTimeline('[data-animation-class="'+i+'"]').attr("data-animation-class",t),function_helpers_1.default.getFromTimeline('.animation-class-name-input[data-old-animation-class="'+i+'"]').val(t)},e.prototype.editAnimationClassNameHandler=function(e){function t(t){var i=t.attr("data-old-animation-class"),a=t.val();t.removeClass("input-tracked-focused"),n.runtimeEditor._sceneActionState.primaryAction="new action",n.editAnimationClassName(e,i,a)}var i=function_helpers_1.default.getFromTimeline('[data-timeline-info-widget-id="'+e+'"] .animation-class-name-input'),n=this;i.off("keypress click focusout"),i.click(function(){$(this).addClass("input-tracked-focused")}).keypress(function(e){if(e.which===enums_1.default.Keys.enter)$(this).blur();else if(e.which===enums_1.default.Keys.space)return!1}).focusout(function(){t($(this))});var a=i.data("kendoTooltip");a&&a.destroy(),i.kendoTooltip({autoHide:!0,showOn:"animationClassDuplicate",content:kendo.template('<div kendoTooltipID="'+e+'" class="tooltip-options tooltip-animation-class"><div class="animation-class-dublicate">Class name already exist. </br> Please choose another one.</div></div>'),width:280,height:75,position:"top"})},e.prototype.editWidgetIdHandler=function(e){function t(e){var t=e.val(),i=e.attr("value"),a=n.runtimeEditor.mappedWidgets[i].widget;e.removeClass("input-tracked-focused"),t!==a.id&&(n.runtimeEditor._sceneActionState.primaryAction="new action",n.runtimeEditor._setProperties(a,e,"element-id","id",t))}var i=function_helpers_1.default.getFromTimeline('[data-timeline-info-widget-id="'+e+'"] .info-widget-name'),n=this;i.off("keypress click focusout"),i.click(function(){$(this).addClass("input-tracked-focused")}).keypress(function(e){if(e.which===enums_1.default.Keys.enter)$(this).blur();else if(e.which===enums_1.default.Keys.space)return!1}).focusout(function(){t($(this))})},e.prototype.editAnimationClassName=function(e,t,i){for(var n=main_1.default.openFiles[main_1.default.selectedEditor],a=n.tab.filename.endsWith(".component"),o=0;o<n.components.state.opened.length;o++){var r=n.components.state.opened[o];if(main_1.default.openFiles[r].runtimeEditor.scene.animationClasses[i])return void(i!==t&&this.triggerDuplicateClassError(t,e))}if(a){var s=n.tab.tabWidgetState.instanceOf,l=main_1.default.openFiles[s];if(JSON.parse(l.file).animationClasses[i])return void(i!==t&&this.triggerDuplicateClassError(t,e))}this.runtimeEditor.scene.animationClasses[i]||i===t?i!==t&&this.triggerDuplicateClassError(t,e):this.runtimeEditor.editAnimationClassName(e,t,i)},e.prototype.triggerDuplicateClassError=function(e,t){var i=function_helpers_1.default.getFromTimeline('[data-timeline-info-widget-id="'+t+'"] .animation-class-name-input');i.trigger("animationClassDuplicate"),i.val(e)},e.prototype.addWidget=function(e,t){var i=this,n=main_1.default.importHtmlTemplate(this.templateTimelineInfo);n.setAttribute("data-timeline-info-widget-id",e.id),n.firstElementChild.firstElementChild.id="anim-option-"+e.id,n.firstElementChild.firstElementChild.value=function_helpers_1.default.shortenString(e.id),n.firstElementChild.firstElementChild.setAttribute("value",e.id),this.$infoWidgetsSection.append(n);var a=main_1.default.importHtmlTemplate(this.templateWidgetLine);a.setAttribute("data-widget-id",e.id),a.setAttribute("value",e.id),function_helpers_1.default.getFromTimeline(".widgets-keyframes-stack").append(a),t&&t.initial&&e.className&&e.className.split(" ").filter(function(t){i.runtimeEditor.scene.animationClasses[t]&&i.initAnimationClassName(e.id,"",t,!0)}),this.createToolTipClassName(e.id),this.addAnimationClassHandler(e),this.removeAnimationClassHandler(e),this.create(),this.editWidgetIdHandler(e.id),function_helpers_1.default.getFromTimeline(".info-widgets").getNiceScroll().resize()},e.prototype.initAnimationClassName=function(e,t,i,n,a){void 0===n&&(n=!1),void 0===a&&(a=!1),this.runtimeEditor.scene.animationClasses[i]=this.runtimeEditor.scene.animationClasses[i]||$.extend(!0,{},enums_1.default.newAnimation),this.runtimeEditor.scene.animationClasses[i].className=i,this.runtimeEditor.scene.animations[e]=this.runtimeEditor.scene.animations[e]||{},a||this.runtimeEditor.switchAnimationClassName(e,t,i,void 0,n),this.setInputClassName(e,i);var o=function_helpers_1.default.getFromTimeline('[data-timeline-info-widget-id="'+e+'"]');o.find(".info-class-name").show(),function_helpers_1.default.getFromTimeline('.widget-name-line[data-widget-id="'+e+'"] .keyframe-line-class-name').show(),this.editAnimationClassNameHandler(e),this.editWidgetIdHandler(e),o.find("animation-class-name-input").show()},e.prototype.createToolTipClassName=function(e){function t(e,t,a){var o=n.runtimeEditor.scene.animationClasses;for(var r in o){var s=document.createElement("option");s.value=r,s.innerHTML=r,r===e&&s.setAttribute("selected","selected"),a[0].appendChild(s)}t.append('<span class="animation-library-title">Animations Library</span>'),t.append('<label class="options-name">Animation:</label>'),t.append(a),a.kendoDropDownList({height:"auto",autoBind:!0,animation:!1,filter:"contains",filtering:function(o){n.animationSearchValue=o.filter.value,i(e,t,a)},dataTextField:"animationClass",dataValueField:"value",headerTemplate:"",valueTemplate:"",template:'<span>#: data.animationClass #</span> <a class="ic-remove-animation-class-global fa fa-remove" data-delete-animation-class="#: data.animationClass #"></a>',open:function(){var o=$(".k-list-filter > input");o.val(n.animationSearchValue),o.trigger("keydown"),i(e,t,a)}})}function i(e,i,o){window.requestAnimationFrame(function(){function_helpers_1.default.getFromTimeline('[data-delete-animation-class="select animation"]').remove(),function_helpers_1.default.getFromTimeline(".ic-remove-animation-class-global").off("click"),function_helpers_1.default.getFromTimeline(".ic-remove-animation-class-global").on("click",function(){var r=$(this).attr("data-delete-animation-class");o.data("kendoDropDownList")&&(o.data("kendoDropDownList").close(),o.data("kendoDropDownList").destroy()),i.empty(),n.runtimeEditor._sceneActionState.primaryAction="new action",n.removeAnimationClassName(r);var s=main_1.default.importHtmlTemplate(a),l=$(s);l.attr("data-old-animation-class",e),t(e,i,l),l.data("kendoDropDownList").open(),n.runtimeEditor.exportScene()})})}var n=this;this.animationSearchValue="";var a=document.querySelector("#animation-class-switch-dropdown"),o=function_helpers_1.default.getFromTimeline('[data-timeline-info-widget-id="'+e+'"] .ic-change-animation-class'),r=o.data("kendoTooltip");r&&r.destroy(),o.kendoTooltip({autoHide:!1,showOn:"click",content:kendo.template('<div kendoTooltipID="'+e+'" class="tooltip-options tooltip-animation-class" data-tooltip-change-class-id="'+e+'"></div>'),width:280,height:75,position:"top",show:function(){var i=$('[data-timeline-info-widget-id="'+e+'"] .info-class-name [data-old-animation-class]').val(),o=$('[data-tooltip-change-class-id="'+e+'"]'),r=main_1.default.importHtmlTemplate(a),s=$(r);s.attr("data-old-animation-class",i),t(i,o,s),n.attachTooltipChangeClassNameHandlers(s,e)},hide:function(){var t=$('[data-tooltip-change-class-id="'+e+'"]');n.resetTooltipHtml(t),n.animationSearchValue=""}})},e.prototype.resetAllTimeline=function(){$(".info-stack").empty(),$(".widgets-keyframes-stack").empty()},e.prototype._addGlobalAnimationClassName=function(e){this.runtimeEditor.scene.animationClasses[e.className]=e,this.runtimeEditor._sceneActionState.addAnimationClassGlobal=!0,this.runtimeEditor.saveUndoRedo(null,null,null,{className:e.className},null),this.runtimeEditor.Animations.loadKeyframes(this.runtimeEditor.scene.animationClasses,!1,!0)},e.prototype._deleteGlobalAnimationClassName=function(e){var t=this.runtimeEditor.scene.animationClasses[e];delete this.runtimeEditor.scene.animationClasses[e],this.runtimeEditor._sceneActionState.deleteAnimationClassGlobal=!0,this.runtimeEditor.saveUndoRedo(null,null,null,t,null)},e.prototype.removeAnimationClassName=function(e){var t=this.runtimeEditor.scene.animationClasses[e];delete this.runtimeEditor.scene.animationClasses[e];var i,n=this.runtimeEditor.scene.animations,a=1;for(i in n)n[i].className===e&&a++;this.runtimeEditor._undoCreationStepsLength=a,this.runtimeEditor._sceneActionState.deleteAnimationClassGlobal=!0,this.runtimeEditor.saveUndoRedo(null,null,null,t,null);for(i in n)n[i].className===e&&this.removeAnimationClassFromWidget(i,e,!0)},e.prototype.attachTooltipChangeClassNameHandlers=function(e,t){var i=this;e.on("change",function(){i.runtimeEditor._sceneActionState.primaryAction="new action",i.runtimeEditor._sceneActionState.switchAnimationClass=!0;var e=$(this).parents(".tooltip-options").find("select.select-animation-class"),n=e.attr("data-old-animation-class"),a=e.val();"remove-animation-class"!==a?(i.runtimeEditor.scene.animations[t]||i.editAnimationClassNameHandler(t),i.runtimeEditor.switchAnimationClassName(t,n,a)):i.removeAnimationClassFromWidget(t,n,!0),i.runtimeEditor._sceneActionState.switchAnimationClass=!1})},e.prototype.addAnimationClassHandler=function(e){var t=this,i=function_helpers_1.default.getFromTimeline('[data-timeline-info-widget-id="'+e.id+'"] .ic-add-animation-class');i.off("click"),i.on("click",function(){t.runtimeEditor._sceneActionState.addNewAnimationClassName=!0;var i=$(this).parents(".widget-timeline-holder").find(".animation-class-name-input").val(),n=main_1.default.generateClassName();t.runtimeEditor._sceneActionState.primaryAction="new action",t.runtimeEditor._sceneActionState.switchAnimationClass=!0,t.initAnimationClassName(e.id,i,n)})},e.prototype.removeAnimationClassHandler=function(e){var t=this,i=function_helpers_1.default.getFromTimeline('[data-timeline-info-widget-id="'+e.id+'"] .ic-remove-animation-class');i.off("click"),i.on("click",function(){var i=$(this).parents(".info-class-name").find(".animation-class-name-input").val();t.runtimeEditor._sceneActionState.primaryAction="new action",t.removeAnimationClassFromWidget(e.id,i,!0)})},e.prototype.removeAnimationClassFromWidget=function(e,t,i){var n="";if(delete this.runtimeEditor.scene.animations[e],i){var a=this.runtimeEditor.mappedWidgets[e].widget.className;""===n&&(n=a.replace(t,"").trim())}this.removeClassNameFromDOM(e,t),this.setInputClassName(e,"",t),this.runtimeEditor.setClassName(null,e,n,!1),function_helpers_1.default.getFromTimeline('[data-timeline-info-widget-id="'+e+'"] .info-class-name').hide(),function_helpers_1.default.getFromTimeline('.widget-name-line[data-widget-id="'+e+'"] .keyframe-line-class-name').hide()},e.prototype.getTooltipHtml=function(e){return main_1.default.Handlebars.compile(tooltipHbs)(e)},e.prototype.resetTooltipHtml=function(e){e.empty(),e.parent().parent().find(".k-list-container.k-popup.k-group.k-reset").remove()},e.prototype.createTooltip=function(e,t,i,n){var a=this,o=e.data("kendoTooltip");o&&o.destroy(),e.kendoTooltip({autoHide:!1,showOn:"click",content:kendo.template('<div class="tooltip-options" kendoTooltipID="'+t.id+'" data-tooltip-id="'+t.id+'" data-tooltip-property-name="'+n+'" data-tooltip-group-name="'+i+'"></div>'),width:280,height:135,position:"top",show:function(){var o=e.parents('[data-timeline-info-widget-id="'+t.id+'"]').find(".animation-class-name-input").val(),r=t[o].animationsData[i][n],s=a.getTooltipHtml(r),l=$('[data-tooltip-id="'+t.id+'"]');l.attr("data-animation-class",o),l.append(s),l.find("select").kendoDropDownList({animation:!1}),a.attachTooltipHandlers(t.id)},hide:function(){var e=$('[data-tooltip-id="'+t.id+'"]');a.resetTooltipHtml(e)}})},e.prototype.attachTooltipHandlers=function(e){var t=this;function_helpers_1.default.getFromTimeline('[data-tooltip-id="'+e+'"] select.animation-timing').on("change",function(e){t.runtimeEditor._sceneActionState.primaryAction="new action";var i=t.collectAnimationData(e);t.setAnimationTiming(i.id,i.group,i.property,i.value,i.className)}),function_helpers_1.default.getFromTimeline('[data-tooltip-id="'+e+'"] input.animation-iteration').on("input",function(e){t.runtimeEditor._sceneActionState.primaryAction="new action";var i=t.collectAnimationData(e);t.setAnimationIteration(i.id,i.group,i.property,i.value,i.className)}),function_helpers_1.default.getFromTimeline('[data-tooltip-id="'+e+'"] input.animation-iteration-loop').on("change",function(i){var n="infinite",a=function_helpers_1.default.getFromTimeline('[data-tooltip-id="'+e+'"] input.animation-iteration');this.checked||(n=a.val()),t.runtimeEditor._sceneActionState.primaryAction="new action";var o=t.collectAnimationData(i);t.setAnimationIteration(o.id,o.group,o.property,n,o.className)}),function_helpers_1.default.getFromTimeline('[data-tooltip-id="'+e+'"] select.animation-direction').on("change",function(e){t.runtimeEditor._sceneActionState.primaryAction="new action";var i=t.collectAnimationData(e);t.setAnimationDirection(i.id,i.group,i.property,i.value,i.className)}),function_helpers_1.default.getFromTimeline('[data-tooltip-id="'+e+'"] input.animation-name').on("input",function(e){t.runtimeEditor._sceneActionState.primaryAction="new action";var i=t.collectAnimationData(e);t.setAnimationName(i.id,i.group,i.property,i.value,i.className)})},e.prototype.collectAnimationData=function(e){var t=$(e.target).parents(".tooltip-options");return{className:t.attr("data-animation-class"),value:$(e.target).val(),id:t.attr("data-tooltip-id"),group:t.attr("data-tooltip-group-name"),property:t.attr("data-tooltip-property-name")}},e.prototype.setAnimationTiming=function(e,t,i,n,a){var o=this.runtimeEditor.scene.animationClasses[a],r={oldValue:o.animationsData[t][i].timing,className:a};if("transform"===t||"-webkit-filter"===t)for(var s in o.animationsData[t])o.animationsData[t][s].timing=n;else o.animationsData[t][i].timing=n;this.runtimeEditor.exportScene(),this.createUndoRedoAnimationOptions(e,t,i,r,"Timing")},e.prototype.setAnimationIteration=function(e,t,i,n,a){var o=this.runtimeEditor.scene.animationClasses[a],r={oldValue:o.animationsData[t][i].iteration,className:a},s=function_helpers_1.default.getFromTimeline('[data-tooltip-id="'+e+'"] input.animation-iteration');if("infinite"===n?s.prop("disabled",!0):s.prop("disabled",!1),"transform"===t||"-webkit-filter"===t)for(var l in o.animationsData[t])o.animationsData[t][l].iteration=n;else o.animationsData[t][i].iteration=n;this.runtimeEditor.exportScene(),this.createUndoRedoAnimationOptions(e,t,i,r,"Iteration")},e.prototype.setAnimationDirection=function(e,t,i,n,a){var o=this.runtimeEditor.scene.animationClasses[a],r={oldValue:o.animationsData[t][i].direction,className:a};if("transform"===t||"-webkit-filter"===t)for(var s in o.animationsData[t])o.animationsData[t][s].direction=n;else o.animationsData[t][i].direction=n;this.runtimeEditor.exportScene(),this.createUndoRedoAnimationOptions(e,t,i,r,"Direction")},e.prototype.setAnimationName=function(e,t,i,n,a){var o=this.runtimeEditor.scene.animationClasses[a],r={oldValue:o.animationsData[t][i].name,className:a};if("transform"===t||"-webkit-filter"===t)for(var s in o.animationsData[t])o.animationsData[t][s].name=n;else o.animationsData[t][i].name=n;this.runtimeEditor.exportScene(),this.createUndoRedoAnimationOptions(e,t,i,r,"Name")},e.prototype.createUndoRedoAnimationOptions=function(e,t,i,n,a){var o=this.runtimeEditor.getRedoUndoPrimaryState(),r={type:a,value:n.oldValue,className:n.className};this.runtimeEditor._sceneActionState.setAnimationOptions=!0,this.runtimeEditor.createUndoRedoCommand(o,e,t,t,i,r)},e.prototype.reinitKendoTooltips=function(e,t,i){if($('[kendoTooltipID="'+e+'"]').attr("kendoTooltipID",t),$('[data-tooltip-id="'+e+'"]').attr("data-tooltip-id",t),$('[data-tooltip-change-class-id="'+e+'"]').attr("data-tooltip-change-class-id",t),this.editAnimationClassNameHandler(t),this.createToolTipClassName(t),i.length>0){var n=$.extend(!0,{},this.runtimeEditor.scene.animations[e]);n.id=t;for(var a=0;a<i.length;a++)for(var o=$(i[a]).find("[data-timeline-info-property-name]"),r=0;r<o.length;r++){var s=$(o[r]).find(".property-name-text").text();if(""!==s){var l=$(o[r]).find('[data-role="tooltip"].animation-options'),d=enums_1.default.WidgetGroups[s];this.createTooltip(l,n,d,s)}}}},e.prototype.editId=function(e,t){var i=function_helpers_1.default.getFromTimeline('[data-timeline-info-widget-id="'+e+'"]'),n=function_helpers_1.default.getFromTimeline('[data-widget-id="'+e+'"]'),a=function_helpers_1.default.getFromTimeline('[data-keyframe-widget-id="'+e+'"]'),o=function_helpers_1.default.getFromTimeline('[data-tooltip-id="'+e+'"]'),r=function_helpers_1.default.getFromTimeline('[data-timeline-info-widget-id="'+e+'"] .info-widget-name');r.val(function_helpers_1.default.shortenString(t)),r.attr("value",function_helpers_1.default.shortenString(t)),i.attr("data-timeline-info-widget-id",t),n.attr("data-widget-id",t),o.attr("data-tooltip-id",t),a.attr("data-keyframe-widget-id",t),this.reinitKendoTooltips(e,t,i)},e}();exports.default=Timeline;