if (typeof NPCInfoModel === 'undefined') {
	engine.createJSModel('NPCInfoModel', {
		CurrentNPCs: 999,
		NPCGenerateCount: 999,
		Actors: [{
			label: 'Test 1',
			top: 200,
			left: 200
		}, {
			label: 'Test 2',
			top: 400,
			left: 400
		}, {
			label: 'Test 3',
			top: 800,
			left: 800
		}],
		init: function () {
			this.updateModel();
		},
		updateModel: function () {
			engine.updateWholeModel(NPCInfoModel);
			engine.synchronizeModels();
		}
	});
	NPCInfoModel.init();
}