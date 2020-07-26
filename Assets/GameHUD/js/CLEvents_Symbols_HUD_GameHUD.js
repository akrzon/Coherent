// !!!WARNING!!!
// This is an automatically generated script! Modify with caution!

//Initialize all the variables
const symbol_Movieclips_DestroyButton = document.getElementsByClassName("Movieclips-DestroyButton");
const symbol_Movieclips_GenerateButton = document.getElementsByClassName("Movieclips-GenerateButton");
const symbol_Movieclips_RightBtn = document.getElementsByClassName("Movieclips-RightBtn");
const symbol_Movieclips_LeftBtn = document.getElementsByClassName("Movieclips-LeftBtn");
const symbol_Movieclips_SliderBg = document.getElementsByClassName("Movieclips-SliderBg");

//mouseleave event for Movieclips_DestroyButton
for (let i_0 = 0; i_0 < symbol_Movieclips_DestroyButton.length; ++i_0) {
    symbol_Movieclips_DestroyButton[i_0].addEventListener("mouseleave", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Default', eventTarget);
    });
}

//mouseenter event for Movieclips_DestroyButton
for (let i_0 = 0; i_0 < symbol_Movieclips_DestroyButton.length; ++i_0) {
    symbol_Movieclips_DestroyButton[i_0].addEventListener("mouseenter", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Highlighted', eventTarget);
    });
}

//mousedown event for Movieclips_DestroyButton
for (let i_0 = 0; i_0 < symbol_Movieclips_DestroyButton.length; ++i_0) {
    symbol_Movieclips_DestroyButton[i_0].addEventListener("mousedown", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Pressed', eventTarget);
    });
}

//mouseup event for Movieclips_DestroyButton
for (let i_0 = 0; i_0 < symbol_Movieclips_DestroyButton.length; ++i_0) {
    symbol_Movieclips_DestroyButton[i_0].addEventListener("mouseup", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Highlighted', eventTarget);
    });
}

//click event for Movieclips_DestroyButton
for (let i_0 = 0; i_0 < symbol_Movieclips_DestroyButton.length; ++i_0) {
    symbol_Movieclips_DestroyButton[i_0].addEventListener("click", (event) => {
        const eventTarget = event.currentTarget;
        // Used for communication with the C++ part
        // For more info: https://coherent-labs.com/Documentation/cpp-hb/df/d01/javascript_virtual_machine.html
        engine.trigger("OnDestroyBtnClicked");
    });
}

//mouseleave event for Movieclips_GenerateButton
for (let i_0 = 0; i_0 < symbol_Movieclips_GenerateButton.length; ++i_0) {
    symbol_Movieclips_GenerateButton[i_0].addEventListener("mouseleave", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Default', eventTarget);
    });
}

//mouseenter event for Movieclips_GenerateButton
for (let i_0 = 0; i_0 < symbol_Movieclips_GenerateButton.length; ++i_0) {
    symbol_Movieclips_GenerateButton[i_0].addEventListener("mouseenter", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Highlighted', eventTarget);
    });
}

//mousedown event for Movieclips_GenerateButton
for (let i_0 = 0; i_0 < symbol_Movieclips_GenerateButton.length; ++i_0) {
    symbol_Movieclips_GenerateButton[i_0].addEventListener("mousedown", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Pressed', eventTarget);
    });
}

//mouseup event for Movieclips_GenerateButton
for (let i_0 = 0; i_0 < symbol_Movieclips_GenerateButton.length; ++i_0) {
    symbol_Movieclips_GenerateButton[i_0].addEventListener("mouseup", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Highlighted', eventTarget);
    });
}

//click event for Movieclips_GenerateButton
for (let i_0 = 0; i_0 < symbol_Movieclips_GenerateButton.length; ++i_0) {
    symbol_Movieclips_GenerateButton[i_0].addEventListener("click", (event) => {
        const eventTarget = event.currentTarget;
        // Used for communication with the C++ part
        // For more info: https://coherent-labs.com/Documentation/cpp-hb/df/d01/javascript_virtual_machine.html
        engine.trigger("OnGenerateBtnClicked");
    });
}

//click event for Movieclips_RightBtn
for (let i_0 = 0; i_0 < symbol_Movieclips_RightBtn.length; ++i_0) {
    symbol_Movieclips_RightBtn[i_0].addEventListener("click", (event) => {
        const eventTarget = event.currentTarget;
        // Used for communication with the C++ part
        // For more info: https://coherent-labs.com/Documentation/cpp-hb/df/d01/javascript_virtual_machine.html
        engine.trigger("OnSliderBtnClicked", "1");
    });
}

//mouseleave event for Movieclips_LeftBtn
for (let i_0 = 0; i_0 < symbol_Movieclips_LeftBtn.length; ++i_0) {
    symbol_Movieclips_LeftBtn[i_0].addEventListener("mouseleave", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Normal', eventTarget);
    });
}

//mouseenter event for Movieclips_LeftBtn
for (let i_0 = 0; i_0 < symbol_Movieclips_LeftBtn.length; ++i_0) {
    symbol_Movieclips_LeftBtn[i_0].addEventListener("mouseenter", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Highlighted', eventTarget);
    });
}

//mouseup event for Movieclips_LeftBtn
for (let i_0 = 0; i_0 < symbol_Movieclips_LeftBtn.length; ++i_0) {
    symbol_Movieclips_LeftBtn[i_0].addEventListener("mouseup", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Highlighted', eventTarget);
    });
}

//mousedown event for Movieclips_LeftBtn
for (let i_0 = 0; i_0 < symbol_Movieclips_LeftBtn.length; ++i_0) {
    symbol_Movieclips_LeftBtn[i_0].addEventListener("mousedown", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Pressed', eventTarget);
    });
}

//click event for Movieclips_LeftBtn
for (let i_0 = 0; i_0 < symbol_Movieclips_LeftBtn.length; ++i_0) {
    symbol_Movieclips_LeftBtn[i_0].addEventListener("click", (event) => {
        const eventTarget = event.currentTarget;
        // Used for communication with the C++ part
        // For more info: https://coherent-labs.com/Documentation/cpp-hb/df/d01/javascript_virtual_machine.html
        engine.trigger("OnSliderBtnClicked", "-1");
    });
}

//wheel event for Movieclips_SliderBg
for (let i_0 = 0; i_0 < symbol_Movieclips_SliderBg.length; ++i_0) {
    symbol_Movieclips_SliderBg[i_0].addEventListener("wheel", (event) => {
        const eventTarget = event.currentTarget;
        engine.trigger("OnSliderBtnClicked", (event.deltaY/40).toString());
    });
}

