"use strict";Object.defineProperty(exports,"__esModule",{value:!0});var main_1=require("../scripts/main"),function_helpers_1=require("./function_helpers"),editor_settings_1=require("./editor_settings"),BuildWidgetHandler;!function(e){var t,o;e.buildWidget=function(e,r,n){t=r||$.extend(!0,{},main_1.default.environmentProperties.DefaultWidget),o=n||{style:{},dataset:{},attributes:{},childNodes:{}},t.type=e;var a=o.style;t.styles.display=a.display||t.styles.display,t.styles.zIndex=a.zIndex||t.styles.zIndex,t.styles.overflow=a.overflow||t.styles.overflow,t.styles.opacity=a.opacity||t.styles.opacity,t.styles.fontWeight=a.fontWeight||t.styles.fontWeight,t.styles.fontStyle=a.fontStyle||t.styles.fontStyle,t.styles.fontFamily=a.fontFamily||t.styles.fontFamily||"initial",t.fontSize=a.fontSize||t.styles.fontSize||"auto",t.color=a.color||t.color;var s=a.top||t.geometry.top,l=a.left||t.geometry.left,d=a.width||t.geometry.width,u=a.height||t.geometry.height;if(a.top){var c=function_helpers_1.default.getUnitStyle(s);s=parseFloat(s).toFixed(2)+c}if(a.left){var g=function_helpers_1.default.getUnitStyle(l);l=parseFloat(l).toFixed(2)+g}if(a.width)if("auto"===a.width)function_helpers_1.default.disableKendoInput("width");else{var f=function_helpers_1.default.getUnitStyle(d);d=parseFloat(d).toFixed(2)+f}if(a.height)if("auto"===a.width)function_helpers_1.default.disableKendoInput("height");else{var b=function_helpers_1.default.getUnitStyle(u);u=parseFloat(u).toFixed(2)+b}if(t.geometry={position:a.position||t.geometry.position,top:s,left:l,width:d,height:u},a.transform&&(t.transform=function_helpers_1.default.createLongPropertyGroup(a.transform)),a.perspective&&(t.styles.perspective=a.perspective),a.transformStyle&&(t.styles.transformStyle=a.transformStyle),a.transformOrigin){var p=a.transformOrigin.split(" ");t["transform-origin"]={},t["transform-origin"]["transform-origin-x"]=function_helpers_1.default.getStringPropertyPercent(p[0])||"50%",t["transform-origin"]["transform-origin-y"]=function_helpers_1.default.getStringPropertyPercent(p[1])||"50%"}if(a.perspectiveOrigin){var m=a.perspectiveOrigin.split(" ");t["perspective-origin"]["perspective-origin-x"]=m[0]||"50%",t["perspective-origin"]["perspective-origin-y"]=m[1]||"50%"}if(o.className&&(t.className=o.className),a.boxShadow){var y=a.boxShadow.split(") ");t.boxShadow=function_helpers_1.default.createBoxShadowPropertyGroup(y[0],y[1])}return editor_settings_1.default.environment.GT===main_1.default.preferences.couiEnvironment&&(t["-coherent-layer-clip-aa"]=a["-coherent-layer-clip-aa"]||"off",o.attributes["data-l10n-id"]?t.attrs["data-l10n-id"]=o.attributes["data-l10n-id"].value:t.attrs["data-l10n-id"]="",a.webkitFilter&&(t["-webkit-filter"]=function_helpers_1.default.createFilterPropertyGroup(a.webkitFilter)),t.styles.mixBlendMode=a.mixBlendMode||"normal"),i[e](),t};var i={};i.video=function(){n(" ")},i.liveview=function(){a.src("liveviewName")},i.responsiveImage=function(){s.width("auto"),s.height("auto"),n(" "),s.responsiveBackgroundImage(""),s.backgroundRepeat("no-repeat"),s.backgroundPositionX("0px"),s.backgroundPositionY("0px"),s.backgroundSize("contain"),s.maskImageFullProps()},i.inputText=function(){s.width("140px"),s.height("26px"),s.padding("2px"),a.value(""),a.placeHolder("placeHolder")},i.range=function(){s.width("100px"),s.height("50px"),s.background("rgba(255, 255, 255, 1)"),a.min("0"),a.max("100"),a.value("0"),a.step("1")},i.number=function(){s.width("60px"),s.height("20px"),a.min("0"),a.max("100"),a.value("0"),a.step("1")},i.flexbox=function(){s.className("flexbox"),s.alignContent("flex-start"),s.alignItems("flex-start"),s.flexDirection("row"),s.flexWrap("nowrap"),s.justifyContent("flex-start"),s.color("rgba(0, 0, 0, 1)"),s.display("flex"),s.backgroundImage("rgba(255, 255, 255, 1)"),s.maskImageFullProps()},i.flexboxChild=function(){s.flex("0 1 auto"),s.order("0"),s.alignSelf("auto"),s.color("rgba(0, 0, 0, 1)"),s.backgroundImage("rgba(255, 255, 255, 1)"),s.maskImageFullProps()},i.option=function(){s.width("60px"),s.height("20px"),a.value("option"),r(t.type),a.select(!1),s.color("rgba(0, 0, 0, 1)")},i.checkbox=function(){s.width("16px"),s.height("16px"),a.checked(!1),s.background("rgba(255, 255, 255, 1)")},i.radio=function(){s.width("16px"),s.height("16px"),s.borderTopLeftRadius("100rem"),s.borderTopRightRadius("100rem"),s.borderBottomLeftRadius("100rem"),s.borderBottomRightRadius("100rem"),s.background("rgba(255, 255, 255, 1)"),a.checked(!1)},i.select=function(){s.width("60px"),s.height("20px"),a.multiple(!1),a.size("1"),s.background("rgba(255, 255, 255, 1)")},i.image=function(){s.width("auto"),s.height("auto"),n(" "),s.maskImageFullProps()},i.textarea=function(){r(t.type),s.background("rgba(255, 255, 255, 1)"),s.color("rgba(0, 0, 0, 1)"),s.borderTopLeftRadius("0rem"),s.borderTopRightRadius("0rem"),s.borderBottomLeftRadius("0rem"),s.borderBottomRightRadius("0rem"),s.borderWidth("0px"),s.borderColor("rgba(0, 0, 0, 1)"),s.borderStyle("solid"),s.display("block"),s.resize("none"),s.userSelect("none")},i.label=function(){s.width("60px"),s.height("20px"),r(t.type),s.background("rgba(255, 255, 255, 0)"),s.color("rgba(0, 0, 0, 1)"),s.textAlign("left")},i.text=function(){r(t.type),s.background("rgba(255, 255, 255, 0)"),s.color("rgba(0, 0, 0, 1)"),s.textAlign("left"),s.textDecoration("node"),s.textTransform("node"),s.maskImageFullProps()},i.ol=function(){s.background("rgba(255, 255, 255, 0)"),s.color("rgba(0, 0, 0, 1)"),s.textAlign("left"),s.textDecoration("node"),s.textTransform("node")},i.li=function(){r(t.type),s.background("rgba(255, 255, 255, 0)"),s.color("rgba(0, 0, 0, 1)"),s.textAlign("left"),s.textDecoration("node"),s.textTransform("node")},i.ul=function(){s.background("rgba(255, 255, 255, 0)"),s.color("rgba(0, 0, 0, 1)")},i.div=function(){n(" "),s.borderTopLeftRadius("0rem"),s.borderTopRightRadius("0rem"),s.borderBottomLeftRadius("0rem"),s.borderBottomRightRadius("0rem"),s.borderWidth("0px"),s.borderColor("rgba(0, 0, 0, 1)"),s.borderStyle("solid"),s.display("block"),s.backgroundImage("rgba(221, 221, 221, 1)"),s.maskImageFullProps()},i.widget=function(){},i.button=function(){r(t.type),s.color("rgba(0, 0, 0, 1)"),s.padding("0px"),s.borderTopLeftRadius("3px"),s.borderTopRightRadius("3px"),s.borderBottomLeftRadius("3px"),s.borderBottomRightRadius("3px"),s.borderWidth("0px"),s.borderColor("rgba(150, 150, 150, 1)"),s.borderStyle("solid"),s.display("block"),n(" "),s.backgroundImage("rgba(221, 221, 221, 1)"),s.maskImageFullProps()},i.roundedRect=function(){s.color("rgba(0, 0, 0, 1)"),s.borderTopLeftRadius("1rem"),s.borderTopRightRadius("1rem"),s.borderBottomLeftRadius("1rem"),s.borderBottomRightRadius("1rem"),s.borderWidth("0px"),s.borderColor("rgba(0, 0, 0, 1)"),s.borderStyle("solid"),s.display("block"),s.backgroundImage("rgba(255, 255, 255, 1)"),s.maskImageFullProps()},i.circle=function(){s.color("rgba(0, 0, 0, 1)"),s.borderTopLeftRadius("100rem"),s.borderTopRightRadius("100rem"),s.borderBottomLeftRadius("100rem"),s.borderBottomRightRadius("100rem"),s.borderWidth("0px"),s.borderColor("rgba(0, 0, 0, 1)"),s.borderStyle("solid"),s.display("block"),s.backgroundImage("rgba(255, 255, 255, 1)"),s.maskImageFullProps()},i.ellipse=function(){s.color("rgba(0, 0, 0, 1)"),s.borderRadius("50%"),s.borderWidth("0px"),s.borderColor("rgba(0, 0, 0, 1)"),s.borderStyle("solid"),s.display("block"),s.backgroundImage("rgba(255, 255, 255, 1)"),s.maskImageFullProps()},i.rectangle=function(){s.color("rgba(0, 0, 0, 1)"),s.borderWidth("0px"),s.borderColor("rgba(0, 0, 0, 1)"),s.borderStyle("solid"),s.display("block"),s.backgroundImage("rgba(255, 255, 255, 1)"),s.maskImageFullProps()};var r=function(e){var i;i=o.childNodes[0]?o.childNodes[0].nodeValue:e,t.text=i},n=function(e){t.url=o.src||e},a={};a.placeHolder=function(e){t.attrs.placeHolder=o.placeholder||e},a.src=function(e){var i=o.attributes.src;i?"liveview"===t.type?t.attrs.src=i.value.replace("liveview://",""):t.attrs.src=i.value:t.attrs.src=e},a.size=function(e){t.attrs.size=o.size||e},a.min=function(e){t.attrs.min=o.min||e},a.max=function(e){t.attrs.max=o.max||e},a.value=function(e){t.attrs.value=o.value||e},a.step=function(e){t.attrs.step=o.step||e},a.select=function(e){t.select=o.select||e},a.checked=function(e){t.checked=o.checked||e},a.multiple=function(e){t.multiple=o.multiple||e};var s={};s.className=function(e){t.className=o.className||e},s.alignContent=function(e){t.styles.alignContent=o.style.alignContent||e},s.alignItems=function(e){t.styles.alignItems=o.style.alignItems||e},s.flexDirection=function(e){t.styles.flexDirection=o.style.flexDirection||e},s.flexWrap=function(e){t.styles.flexWrap=o.style.flexWrap||e},s.justifyContent=function(e){t.styles.justifyContent=o.style.justifyContent||e},s.padding=function(e){editor_settings_1.default.environment.GT===main_1.default.preferences.couiEnvironment&&(t.styles.padding=o.style.padding||e)},s.borderTopLeftRadius=function(e){t.styles.borderTopLeftRadius=o.style.borderTopLeftRadius||e},s.borderTopRightRadius=function(e){t.styles.borderTopRightRadius=o.style.borderTopRightRadius||e},s.borderBottomLeftRadius=function(e){t.styles.borderBottomLeftRadius=o.style.borderBottomLeftRadius||e},s.borderBottomRightRadius=function(e){t.styles.borderBottomRightRadius=o.style.borderBottomRightRadius||e},s.borderWidth=function(e){t.styles.borderWidth=o.style.borderWidth||e},s.borderRadius=function(e){t.styles.borderRadius=o.style.borderRadius||e},s.borderColor=function(e){t.styles.borderColor=o.style.borderColor||e},s.borderStyle=function(e){t.styles.borderStyle=o.style.borderStyle||e},s.width=function(e){t.geometry.width=o.style.width||e},s.height=function(e){t.geometry.height=o.style.height||e},s.display=function(e){t.styles.display=o.style.display||e},s.color=function(e){t.color=o.style.color||e},s.background=function(e){t.background=o.style.backgroundColor||e},s.flex=function(e){t.styles.flex=o.style.flex||e},s.order=function(e){t.styles.order=o.style.order||e},s.alignSelf=function(e){t.styles.alignSelf=o.style.alignSelf||e},s.backgroundRepeat=function(e){t.styles.backgroundRepeat=o.style.backgroundRepeat||e},s.backgroundPositionX=function(e){t.styles.backgroundPositionX=o.style.backgroundPositionX||e},s.backgroundPositionY=function(e){t.styles.backgroundPositionY=o.style.backgroundPositionY||e},s.backgroundSize=function(e){var i=o.style,r=t.styles;if(r.backgroundSizeWidth||(r.backgroundSizeWidth="auto"),r.backgroundSizeHeight||(r.backgroundSizeHeight="auto"),i.backgroundSize){var n=i.backgroundSize;if("inherit"!==n&&"cover"!==n&&"contain"!==n){var a=n.split(" ");r.backgroundSize="auto",r.backgroundSizeWidth=a[0],1===a.length?r.backgroundSizeHeight="auto":r.backgroundSizeHeight=a[1]}else r.backgroundSize=n}else r.backgroundSize="contain"},s.responsiveBackgroundImage=function(e){t.styles.backgroundImage=o.style.backgroundImage||e},s.backgroundImage=function(e){var i=o.style;i.backgroundImage&&"initial"!==i.backgroundImage?t.background=i.backgroundImage||e:t.background=i.backgroundColor||e},s.textAlign=function(e){editor_settings_1.default.environment.GT===main_1.default.preferences.couiEnvironment&&(t.styles.textAlign=o.style.textAlign||e)},s.textTransform=function(e){editor_settings_1.default.environment.GT===main_1.default.preferences.couiEnvironment&&(t.styles.textTransform=o.style.textTransform||e)},s.textDecoration=function(e){editor_settings_1.default.environment.GT===main_1.default.preferences.couiEnvironment&&(t.styles.textDecoration=o.style.textDecoration||e)},s.maskImageFullProps=function(){"no-repeat"!==o.style.webkitMask?(this.maskPositionX("0px"),this.maskPositionY("0px"),this.maskSize("contain"),this.maskRepeat("no-repeat"),this.maskImage(" ")):o.style.webkitMask=""},s.maskImage=function(e){o.style.webkitMaskImage&&"initial"!==o.style.webkitMaskImage?t.styles.webkitMaskImage=o.style.webkitMaskImage:t.styles.webkitMaskImage=e},s.maskPositionX=function(e){t.styles["-webkit-mask-position-x"]=o.style.webkitMaskPositionX||e},s.maskPositionY=function(e){t.styles["-webkit-mask-position-y"]=o.style.webkitMaskPositionY||e},s.maskSize=function(e){var i=o.style,r=t.styles;if(r["-webkit-mask-sizeWidth"]||(r["-webkit-mask-sizeWidth"]="auto"),r["-webkit-mask-sizeHeight"]||(r["-webkit-mask-sizeHeight"]="auto"),i["-webkit-mask-size"]){var n=function_helpers_1.default.maskSizeFormat(i["-webkit-mask-size"]);if("inherit"!==n&&"cover"!==n&&"contain"!==n){var a=n.split(" ");r["-webkit-mask-size"]="auto",r["-webkit-mask-sizeWidth"]=a[0],1===a.length?r["-webkit-mask-sizeHeight"]="auto":r["-webkit-mask-sizeHeight"]=a[1]}else r["-webkit-mask-size"]=n}else r["-webkit-mask-size"]="contain"},s.maskRepeat=function(e){t.styles.webkitMaskRepeat=o.style.webkitMaskRepeat||e},s.resize=function(e){t.styles.resize=o.style.resize||e},s.userSelect=function(e){t.styles.webkitUserSelect=o.style.webkitUserSelect||e}}(BuildWidgetHandler||(BuildWidgetHandler={})),exports.default=BuildWidgetHandler;