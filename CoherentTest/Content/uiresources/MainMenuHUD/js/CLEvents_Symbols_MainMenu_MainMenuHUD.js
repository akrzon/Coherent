// !!!WARNING!!!
// This is an automatically generated script! Modify with caution!

//Initialize all the variables
const symbol_Movieclips_StartButton = document.getElementsByClassName("Movieclips-StartButton");
const symbol_Movieclips_AnimButton = document.getElementsByClassName("Movieclips-AnimButton");
const symbol_Movieclips_QuitButton = document.getElementsByClassName("Movieclips-QuitButton");

//mouseleave event for Movieclips_StartButton
for (let i_0 = 0; i_0 < symbol_Movieclips_StartButton.length; ++i_0) {
    symbol_Movieclips_StartButton[i_0].addEventListener("mouseleave", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Default', eventTarget);
    });
}

//mouseenter event for Movieclips_StartButton
for (let i_0 = 0; i_0 < symbol_Movieclips_StartButton.length; ++i_0) {
    symbol_Movieclips_StartButton[i_0].addEventListener("mouseenter", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Highlighted', eventTarget);
    });
}

//mousedown event for Movieclips_StartButton
for (let i_0 = 0; i_0 < symbol_Movieclips_StartButton.length; ++i_0) {
    symbol_Movieclips_StartButton[i_0].addEventListener("mousedown", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Pressed', eventTarget);
    });
}

//mouseup event for Movieclips_StartButton
for (let i_0 = 0; i_0 < symbol_Movieclips_StartButton.length; ++i_0) {
    symbol_Movieclips_StartButton[i_0].addEventListener("mouseup", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Highlighted', eventTarget);
    });
}

//click event for Movieclips_StartButton
for (let i_0 = 0; i_0 < symbol_Movieclips_StartButton.length; ++i_0) {
    symbol_Movieclips_StartButton[i_0].addEventListener("click", (event) => {
        const eventTarget = event.currentTarget;
        // Used for communication with the C++ part
        // For more info: https://coherent-labs.com/Documentation/cpp-hb/df/d01/javascript_virtual_machine.html
        engine.trigger("OnStartBtnClicked");
    });
}

//mouseleave event for Movieclips_AnimButton
for (let i_0 = 0; i_0 < symbol_Movieclips_AnimButton.length; ++i_0) {
    symbol_Movieclips_AnimButton[i_0].addEventListener("mouseleave", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Default', eventTarget);
    });
}

//mouseenter event for Movieclips_AnimButton
for (let i_0 = 0; i_0 < symbol_Movieclips_AnimButton.length; ++i_0) {
    symbol_Movieclips_AnimButton[i_0].addEventListener("mouseenter", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Highlighted', eventTarget);
    });
}

//mousedown event for Movieclips_AnimButton
for (let i_0 = 0; i_0 < symbol_Movieclips_AnimButton.length; ++i_0) {
    symbol_Movieclips_AnimButton[i_0].addEventListener("mousedown", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Pressed', eventTarget);
    });
}

//mouseup event for Movieclips_AnimButton
for (let i_0 = 0; i_0 < symbol_Movieclips_AnimButton.length; ++i_0) {
    symbol_Movieclips_AnimButton[i_0].addEventListener("mouseup", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Highlighted', eventTarget);
    });
}

//click event for Movieclips_AnimButton
for (let i_0 = 0; i_0 < symbol_Movieclips_AnimButton.length; ++i_0) {
    symbol_Movieclips_AnimButton[i_0].addEventListener("click", (event) => {
        const eventTarget = event.currentTarget;
        const targetElements_1 = document.querySelector(".Movieclips-MeteorAnim_mc.MeteorAnim_obj");

        CLAnimations.gotoAndPlay('Start', targetElements_1);
    });
}

//mouseleave event for Movieclips_QuitButton
for (let i_0 = 0; i_0 < symbol_Movieclips_QuitButton.length; ++i_0) {
    symbol_Movieclips_QuitButton[i_0].addEventListener("mouseleave", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Default', eventTarget);
    });
}

//mouseenter event for Movieclips_QuitButton
for (let i_0 = 0; i_0 < symbol_Movieclips_QuitButton.length; ++i_0) {
    symbol_Movieclips_QuitButton[i_0].addEventListener("mouseenter", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Highlighted', eventTarget);
    });
}

//mousedown event for Movieclips_QuitButton
for (let i_0 = 0; i_0 < symbol_Movieclips_QuitButton.length; ++i_0) {
    symbol_Movieclips_QuitButton[i_0].addEventListener("mousedown", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Pressed', eventTarget);
    });
}

//mouseup event for Movieclips_QuitButton
for (let i_0 = 0; i_0 < symbol_Movieclips_QuitButton.length; ++i_0) {
    symbol_Movieclips_QuitButton[i_0].addEventListener("mouseup", (event) => {
        const eventTarget = event.currentTarget;

        CLAnimations.gotoAndStop('Highlighted', eventTarget);
    });
}

//click event for Movieclips_QuitButton
for (let i_0 = 0; i_0 < symbol_Movieclips_QuitButton.length; ++i_0) {
    symbol_Movieclips_QuitButton[i_0].addEventListener("click", (event) => {
        const eventTarget = event.currentTarget;
        // Used for communication with the C++ part
        // For more info: https://coherent-labs.com/Documentation/cpp-hb/df/d01/javascript_virtual_machine.html
        engine.trigger("OnQuitBtnClicked");
    });
}

