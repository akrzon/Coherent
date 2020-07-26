// !!!WARNING!!!
// This is an automatically generated script! Modify with caution!
const LABEL_KEY_ATTRIBUTE_NAME = 'cl-labels-key';

class CallbackCounter {
    constructor(callback = null) {
        this.count = 0;
        this.callback = callback;
    }

    reduceCount(arg) {
        if (--this.count == 0) {
            window.requestAnimationFrame(this.callback);
        }
        if (arg.target) {
            arg.target.onfinish = function () { };
        } else {
            arg.onfinish = function () { };
        }
    }

    increaseCount(number) {
        this.count += number;
    }
}

class CLAnimations {
    /**
     * Retrieves the correct target element from the DOM. 
     * @param {string} target - The class name of the element.
     * @param {string} sceneName - The scene name (equal to html page name)
     * @returns {HTMLElement} - Returns the matched DOM element
     */
    static getTargetElement(target, sceneName) {
        let targetElement;

        if (target === sceneName) {
            targetElement = document.getElementsByTagName("body")[0];
        } else {
            targetElement = document.querySelector('.' + target);
        }

        return targetElement;
    }

    /**
     * Get the label time in the target's timeline
     * @param {string} sceneName - The scene name (equal to html page name)
     * @param {string|HTMLElement} target - The class name of the element. Or a DOM element
     * @param {string} labelName - The name of the label
     * @param {boolean} isGlobalAnimation - If the targetAnimation is the Scene
     * @returns {number} - Returns the time of the label
     */
    static getLabelTime(sceneName, target, labelName, isGlobalAnimation) {
        const timelineArr = !isGlobalAnimation
            ? InstanceAnimations[target]
            : InstanceAnimations['global_animations'][sceneName];

        if (!timelineArr) return;

        for (let layer in timelineArr) {
            for (let labelObj of timelineArr[layer]) {
                if (labelObj[labelName] !== undefined) {
                    return labelObj[labelName];
                }
            }
        }
    }

    /**
     * Get the label time from specific layer in the target's timeline
     * @param {string} sceneName - The scene name (equal to html page name)
     * @param {string|HTMLElement} target - The class name of the element. Or a DOM element
     * @param {string} labelName - The name of the label
     * @param {string} layerName - Specific layer name where the label is located
     * @param {boolean} isGlobalAnimation - If the target animation is the Scene
     * @returns {number} - Returns the time of the label
     */
    static getLabelTimeInLayer(sceneName, target, labelName, layerName, isGlobalAnimation) {
        const timelineArr = !isGlobalAnimation
            ? InstanceAnimations[target][layerName]
            : InstanceAnimations['global_animations'][sceneName][layerName];

        if (!timelineArr) return;

        for (let labelObj of timelineArr) {
            if (labelObj[labelName] !== undefined) {
                return labelObj[labelName];
            }
        }
    }

    /**
     * Used to validate if the target exists and has labels in the collection with labels
     * If target exists then the target data will be returned
     * @param {string|HTMLElement} target - The class name of the element. Or a DOM element
     * @param {string} sceneName - The current scene name
     * @returns {object|boolean} - Response from the validation. False if the target is not valid.
     * Object with the target's "cl-labels-key", the target corresponding DOM element and boolean if the target's animation is global
     */
    static getTargetData(target, sceneName) {
        if (!target) {
            console.warn('Target is ' + target);
            return false;
        }

        const isDomElement = target instanceof Element;

        if (target === 'Current scene') {
            target = sceneName;
        }

        let isGlobalAnimation;
        let targetElement;

        if (isDomElement) {
            targetElement = target;
        } else {
            targetElement = this.getTargetElement(target, sceneName);

            if (!targetElement) {
                console.warn('CLAnimations didn\'t find DOM element with class name ' + target);
                return false;
            }
        }

        if (target !== sceneName) {
            target = targetElement.getAttribute(LABEL_KEY_ATTRIBUTE_NAME);

            if (InstanceAnimations[target] === undefined) {
                console.warn(target + ' does not have labels');
                return false;
            }

            isGlobalAnimation = false;
        } else {
            isGlobalAnimation = true;
        }

        return { target: target, targetElement: targetElement, isGlobalAnimation: isGlobalAnimation };
    }

    /**
     * Used to validate the passed lable name if it exists in the collection with labels
     * @param {string|HTMLElement} target - The class name of the element. Or a DOM element
     * @param {string} label - The lable name you want to play
     * @param {number} labelTime - The resolved label time
     * @param {object} optional - Optional parameters from the main method
     */
    static isLabelValid(target, label, labelTime, optional) {
        if (labelTime === undefined && optional.labelLayer) {
            console.warn('"' + target + '" does not have label "' + label + '" in layer "' + optional.labelLayer + '"');
            return false;

        } else if (labelTime === undefined) {
            console.warn('"' + target + '" does not have label "' + label + '"');
            return false;
        }

        return true;
    }

    /**
     * Custom trigger of gotoAndPlay animation of some element
     * @param {string} label - The lable name you want to play
     * @param {string|HTMLElement} target - The class name of the element. Or a DOM element
     * @param {object} optional - Optional parameters of the method
     * @param {string} optional.labelLayer - Specific layer where the label is located
     * @param {boolean} optional.nestedAnimations - If the nested animations should be played too
     * @param {function} optional.callback - Callback when the animation ends
     */
    static gotoAndPlay(label, target, optional = {}) {
        const sceneName = window.location.pathname
            .split('/')
            .slice(-1)[0]
            .replace('.html', '');

        const targetData = this.getTargetData(target, sceneName);

        if (!targetData) {
            return;
        }

        const targetElement = targetData.targetElement;
        const isGlobalAnimation = targetData.isGlobalAnimation;

        target = targetData.target;

        const labelTime = optional.labelLayer
            ? this.getLabelTimeInLayer(sceneName, target, label, optional.labelLayer, isGlobalAnimation)
            : this.getLabelTime(sceneName, target, label, isGlobalAnimation);

        if (!this.isLabelValid(target, label, labelTime, optional)) {
            return;
        }

        const symbolTarget = targetElement;
        const symbolChildrentarget = optional.nestedAnimations ? symbolTarget.querySelectorAll('*') : symbolTarget.children;
        const symbolChildrenLengthTarget = symbolChildrentarget.length;
        const cbCounter = new CallbackCounter(optional.callback);

        for (let i = 0; i < symbolChildrenLengthTarget; i++) {
            const currentChildElement = symbolChildrentarget[i];

            if (this.isMaskElement(currentChildElement) && !optional.nestedAnimations) {
                this.playMaskAnimation(currentChildElement, optional, this.gotoAndPlayCallback, [labelTime, cbCounter])
            } else {
                this.gotoAndPlayCallback(currentChildElement, labelTime, cbCounter);
            }
        }
    }

    /**
     * Callback for playing an animations starting from a specific time
     * @param {HTMLElement} symbolChildrentarget - The element with animations which will be played
     * @param {number} labelTime - The label time that animation will start playing
     * @param {CallbackCounter} cbCounter - The callback counter which will execute the callback when the full animation ends
     */
    static gotoAndPlayCallback(symbolChildrentarget, labelTime, cbCounter) {
        const childAnimations = symbolChildrentarget.getAnimations();
        const childAnimationsLength = childAnimations.length;
        cbCounter.increaseCount(childAnimationsLength);

        for (let j = 0; j < childAnimationsLength; j++) {
            if (cbCounter.callback) {
                childAnimations[j].onfinish = cbCounter.reduceCount.bind(cbCounter);
            }

            childAnimations[j].play();
            childAnimations[j].currentTime = labelTime * 1000;
        }
    }

    /**
     * Custom trigger of gotoAndStop animation of some element
     * @param {string} label - The lable name you want to stop
     * @param {string|HTMLElement} target - The class name of the element. Or a DOM element
     * @param {object} optional - Optional parameters of the method
     * @param {string} optional.labelLayer - Specific layer where the label is located
     * @param {boolean} optional.nestedAnimations - If the nested animations should be paused too
     */
    static gotoAndStop(label, target, optional = {}) {
        const sceneName = window.location.pathname
            .split('/')
            .slice(-1)[0]
            .replace('.html', '');

        const targetData = this.getTargetData(target, sceneName);

        if (!targetData) {
            return;
        }

        const targetElement = targetData.targetElement;
        const isGlobalAnimation = targetData.isGlobalAnimation;

        target = targetData.target;

        const labelTime = optional.labelLayer
            ? this.getLabelTimeInLayer(sceneName, target, label, optional.labelLayer, isGlobalAnimation)
            : this.getLabelTime(sceneName, target, label, isGlobalAnimation);

        if (!this.isLabelValid(target, label, labelTime, optional)) {
            return;
        }

        const symbolTarget = targetElement;
        const symbolChildrentarget = optional.nestedAnimations ? symbolTarget.querySelectorAll('*') : symbolTarget.children;
        const symbolChildrenLengthTarget = symbolChildrentarget.length;

        for (let i = 0; i < symbolChildrenLengthTarget; i++) {
            const currentChildElement = symbolChildrentarget[i];

            if (this.isMaskElement(currentChildElement) && !optional.nestedAnimations) {
                this.playMaskAnimation(currentChildElement, optional, this.gotoAndStopCallback, [labelTime])
            } else {
                this.gotoAndStopCallback(currentChildElement, labelTime);
            }
        }
    }

    /**
     * Callback for stopping an animations in a specific time
     * @param {HTMLElement} symbolChildrentarget - The element with animations which will be played
     * @param {number} labelTime - The label time that animation will stop playing
     */
    static gotoAndStopCallback(symbolChildrentarget, labelTime) {
        const childAnimations = symbolChildrentarget.getAnimations();
        const childAnimationsLength = childAnimations.length;

        for (let j = 0; j < childAnimationsLength; j++) {
            childAnimations[j].play();
            childAnimations[j].pause();
            childAnimations[j].currentTime = labelTime * 1000;
        }
    }

    /**
     * Custom trigger of playFromTo animation of some element
     * @param {string} fromLabel - The lable name you want to play from
     * @param {string} toLabel - The lable name you want to play to
     * @param {string|HTMLElement} target - The class name of the element. Or a DOM element
     * @param {object} optional - Optional parameters of the method
     * @param {string} optional.fromLabelLayer - Specific layer where the fromLabel is located
     * @param {string} optional.toLabelLayer - Specific layer where the toLabel is located
     * @param {boolean} optional.nestedAnimations - If the nested animations should be played too
     * @param {function} optional.callback - Callback when the animation ends
     */
    static playFromTo(fromLabel, toLabel, target, optional = {}) {
        const sceneName = window.location.pathname
            .split('/')
            .slice(-1)[0]
            .replace('.html', '');

        const targetData = this.getTargetData(target, sceneName);

        if (!targetData) {
            return;
        }

        const targetElement = targetData.targetElement;
        const isGlobalAnimation = targetData.isGlobalAnimation;

        target = targetData.target;

        const fromLabelTime = optional.fromLabelLayer
            ? this.getLabelTimeInLayer(sceneName, target, fromLabel, optional.fromLabelLayer, isGlobalAnimation)
            : this.getLabelTime(sceneName, target, fromLabel, isGlobalAnimation);

        if (!this.isLabelValid(target, fromLabel, fromLabelTime, optional)) {
            return;
        }

        const toLabelTime = optional.toLabelLayer
            ? this.getLabelTimeInLayer(sceneName, target, toLabel, optional.toLabelLayer, isGlobalAnimation)
            : this.getLabelTime(sceneName, target, toLabel, isGlobalAnimation);

        if (!this.isLabelValid(target, toLabel, toLabelTime, optional)) {
            return;
        }

        const symbolTarget = targetElement;
        const symbolChildrentarget = optional.nestedAnimations ? symbolTarget.querySelectorAll('*') : symbolTarget.children;
        const symbolChildrenLengthTarget = symbolChildrentarget.length;
        const cbCounter = new CallbackCounter(optional.callback);

        for (let i = 0; i < symbolChildrenLengthTarget; i++) {
            const currentChildElement = symbolChildrentarget[i];

            if (this.isMaskElement(currentChildElement) && !optional.nestedAnimations) {
                this.playMaskAnimation(currentChildElement, optional, this.playFromToCallback, [fromLabelTime, toLabelTime, cbCounter])
            } else {
                this.playFromToCallback(currentChildElement, fromLabelTime, toLabelTime, cbCounter);
            }
        }
    }

    /**
     * Callback for playing "from"-"to" an animations
     * @param {HTMLElement} symbolChildrentarget - The element with animations which will be played
     * @param {number} fromLabelTime - The label time that animation will start playing
     * @param {number} toLabelTime - The label time that animation will stop playing
     * @param {CallbackCounter} cbCounter - The callback counter which will execute the callback when the full animation ends
     */
    static playFromToCallback(symbolChildrentarget, fromLabelTime, toLabelTime, cbCounter) {
        const childAnimations = symbolChildrentarget.getAnimations();
        const childAnimationsLength = childAnimations.length;
        cbCounter.increaseCount(childAnimationsLength);

        for (let j = 0; j < childAnimationsLength; j++) {
            if (cbCounter.callback) {
                childAnimations[j].onfinish = cbCounter.reduceCount.bind(cbCounter);
                childAnimations[j].playFromTo(fromLabelTime * 1000, toLabelTime * 1000, cbCounter.reduceCount.bind(cbCounter, childAnimations[j]));
            } else {
                childAnimations[j].playFromTo(fromLabelTime * 1000, toLabelTime * 1000);
            }
        }
    }

    /**
     * Play the animation of some element
     * @param {string|HTMLElement} target - The class name of the element. Or a DOM element
     * @param {object} optional - Optional parameters of the method
     * @param {boolean} optional.nestedAnimations - If the nested animations should be played too
     * @param {function} optional.callback - Callback when the animation ends
     */
    static play(target, optional = {}) {
        const sceneName = window.location.pathname
            .split('/')
            .slice(-1)[0]
            .replace('.html', '');

        const targetData = this.getTargetData(target, sceneName);

        if (!targetData) {
            return;
        }

        const targetElement = targetData.targetElement;

        const symbolTarget = targetElement;
        const symbolChildrentarget = optional.nestedAnimations ? symbolTarget.querySelectorAll('*') : symbolTarget.children;
        const symbolChildrenLengthTarget = symbolChildrentarget.length;
        const cbCounter = new CallbackCounter(optional.callback);

        for (let i = 0; i < symbolChildrenLengthTarget; i++) {
            const currentChildElement = symbolChildrentarget[i];

            if (this.isMaskElement(currentChildElement) && !optional.nestedAnimations) {
                this.playMaskAnimation(currentChildElement, optional, this.playCallback, [cbCounter])
            } else {
                this.playCallback(currentChildElement, cbCounter);
            }
        }
    }

    /**
     * Callback for playing an animations
     * @param {HTMLElement} symbolChildrentarget - The element with animations which will be played
     * @param {CallbackCounter} cbCounter - The callback counter which will execute the callback when the full animation ends
     */
    static playCallback(symbolChildrentarget, cbCounter) {
        const childAnimations = symbolChildrentarget.getAnimations();
        const childAnimationsLength = childAnimations.length;
        cbCounter.increaseCount(childAnimationsLength);

        for (let j = 0; j < childAnimationsLength; j++) {
            if (cbCounter.callback) {
                childAnimations[j].onfinish = cbCounter.reduceCount.bind(cbCounter);
            }

            childAnimations[j].play();
            childAnimations[j].currentTime = 0;
        }
    }

    /**
     * Pause the animation of some element
     * @param {string|HTMLElement} target - The class name of the element. Or a DOM element
     * @param {object} optional - Optional parameters of the method
     * @param {boolean} optional.nestedAnimations - If the nested animations should be paused too
     */
    static pause(target, optional = {}) {
        const sceneName = window.location.pathname
            .split('/')
            .slice(-1)[0]
            .replace('.html', '');

        const targetData = this.getTargetData(target, sceneName);

        if (!targetData) {
            return;
        }

        const targetElement = targetData.targetElement;

        const symbolTarget = targetElement;
        const symbolChildrentarget = optional.nestedAnimations ? symbolTarget.querySelectorAll('*') : symbolTarget.children;
        const symbolChildrenLengthTarget = symbolChildrentarget.length;

        for (let i = 0; i < symbolChildrenLengthTarget; i++) {
            const currentChildElement = symbolChildrentarget[i];

            if (this.isMaskElement(currentChildElement)) {
                this.playMaskAnimation(currentChildElement, optional, this.pauseCallback, [])
            } else {
                this.pauseCallback(currentChildElement);
            }
        }
    }

    /**
     * Callback for pausing an animations
     * @param {HTMLElement} symbolChildrentarget - The element with animations which will be paused
     */
    static pauseCallback(symbolChildrentarget) {
        const childAnimations = symbolChildrentarget.getAnimations();
        const childAnimationsLength = childAnimations.length;

        for (let j = 0; j < childAnimationsLength; j++) {
            childAnimations[j].pause();
        }
    }

    /**
     * Used to play an animation inside mask element
     * @param {HTMLElement} targetElement - The DOM target element
     * @param {object} optional - Optional params
     * @param {function} callback - The callback which will be executed for playing/pausing an animation
     * @param {array} callbackArgs - Array with arguments for the callback. For different callbacks args could be label times or optional params
     */
    static playMaskAnimation(targetElement, optional, callback, callbackArgs) {
        //playing the top layer if it has an animation via the callback passed for playing an animation
        callback.apply(this, [targetElement, ...callbackArgs]);

        const symbolTarget = targetElement;
        const symbolChildrentarget = optional.nestedAnimations ? symbolTarget.querySelectorAll('*') : symbolTarget.children;
        const symbolChildrenLengthTarget = symbolChildrentarget.length;

        for (let i = 0; i < symbolChildrenLengthTarget; i++) {
            callback.apply(this, [symbolChildrentarget[i], ...callbackArgs]);
        }
    }

    /**
     * Check if the passed element is a mask
     * @param {HTMLElement} element - DOM element to be checked if it is a mask
     */
    static isMaskElement(element) {
        const elementStyles = getComputedStyle(element);

        return elementStyles.clipPath !== 'none' || elementStyles.maskImage !== 'none';
    }

    /**
     * Get the labels of some element
     * @param {string|HTMLElement} target - The class name of the element. Or a DOM element
     * @returns {object} - Returns an object with the labels of the element grouped by layer
     */
    static getElementLabels(target) {
        const sceneName = window.location.pathname
            .split('/')
            .slice(-1)[0]
            .replace('.html', '');

        const targetData = this.getTargetData(target, sceneName);

        if (!targetData) {
            return;
        }
        const isGlobalAnimation = targetData.isGlobalAnimation;

        target = targetData.target;

        if (isGlobalAnimation) {
            return InstanceAnimations['global_animations'][target];
        } else {
            return InstanceAnimations[target];
        }
    }
}