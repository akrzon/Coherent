engine.createJSModel('mainMenuModel', {
	buttons: [{
		id: 0,
		label: 'Play Animation',
		functionName: "OnAnimBtnClicked"
	}, {
		id: 1,
		label: 'Start',
		functionName: "OnStartBtnClicked"
	}, {
		id: 2,
		label: 'Quit',
		functionName: "OnQuitBtnClicked"
	}],
    init: function () {
        this.updateModel();
    },
    updateModel: function () {
        engine.updateWholeModel(mainMenuModel);
        engine.synchronizeModels();
    }
});
mainMenuModel.init();