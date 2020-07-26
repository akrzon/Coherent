function MakeOverhead() {
    var plate = document.createElement('div');
    plate.className = "Overhead";

    return plate;
}

function CreateOverhead() {
    var plate = MakeOverhead();
    document.body.appendChild(plate);
	console.log('Overhead created');
}

engine.on('CreateOverhead', CreateOverhead);