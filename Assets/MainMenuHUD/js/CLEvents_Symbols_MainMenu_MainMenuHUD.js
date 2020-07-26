// !!!WARNING!!!
// This is an automatically generated script! Modify with caution!

//Initialize all the variables
const symbol_Movieclips_Button = document.getElementsByClassName("Movieclips-Button");

//Callback for mouseleave in Movieclips_Button
function cb_0(event, element, model) {
    const eventTarget = event.currentTarget;

    CLAnimations.gotoAndStop('Default', eventTarget);
}

//Callback for mouseenter in Movieclips_Button
function cb_1(event, element, model) {
    const eventTarget = event.currentTarget;

    CLAnimations.gotoAndStop('Highlighted', eventTarget);
}

//Callback for mousedown in Movieclips_Button
function cb_2(event, element, model) {
    const eventTarget = event.currentTarget;

    CLAnimations.gotoAndStop('Pressed', eventTarget);
}

//Callback for mouseup in Movieclips_Button
function cb_3(event, element, model) {
    const eventTarget = event.currentTarget;

    CLAnimations.gotoAndStop('Highlighted', eventTarget);
}

//Callback for click in Movieclips_Button
function cb_4(event, element, model) {
    const eventTarget = event.currentTarget;
    console.log(model.functionName);
    engine.trigger(model.functionName);
}

