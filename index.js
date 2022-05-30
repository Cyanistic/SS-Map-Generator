let bpm, divisor, length, eval1, eval2, storeNote, wLoop = 0, noteNum, timeBetween, timeAt, audioID, startTime
let eval1s = []
let jumpNote = []
let spiralNote = []
var resObj = {result: 0}

for(let i = 0; i < 9; i++)
{
    jumpNote[i] =[]
    spiralNote[i] =[]
    for (let g =0; g < 12; g++)
    {
        jumpNote[i][g] = null
        spiralNote[i][g] = null
    }
    for(let g=12; g<15; g++)
    {
        jumpNote[i][g] = null
    }
}

spiralNote = [ [1,3,1,3,1,3,1,3,1,3,1,3], [0,2,4,0,2,4,0,2,4,0,2,4], [1,5,1,5,1,5,1,5,1,5,1,5], [0,4,6,0,4,6,0,4,6,0,4,6], [1,3,5,7,1,3,5,7,1,3,5,7], [2,4,8,2,4,8,2,4,8,2,4,8], [3,7,3,7,3,7,3,7,3,7,3,7], [4,6,8,4,6,8,4,6,8,4,6,8], [5,7,5,7,5,7,5,7,5,7,5,7] ]
jumpNote = [[2,5,6,7,8,2,5,6,7,8,2,5,6,7,8],[6,7,8,6,7,8,6,7,8,6,7,8,6,7,8],[0,3,6,7,8,0,3,6,7,8,0,3,6,7,8],[2,5,8,2,5,8,2,5,8,2,5,8,2,5,8],[-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],[0,3,6,0,3,6,0,3,6,0,3,6,0,3,6],[0,1,2,5,8,0,1,2,5,8,0,1,2,5,8],[0,1,2,0,1,2,0,1,2,0,1,2,0,1,2],[0,1,2,3,6,0,1,2,3,6,0,1,2,3,6] ]

function randomSpiral( eval1, eval2, storeNote, wLoop, noteNum, timeBetween, timeAt, eval1s, spiralNote, resObj, startTime)
{
    let centerCheck = [ 0,7,0,5,0,3,0,1,0 ];
	while (wLoop < noteNum)
	{
		storeNote = spiralNote[eval1][eval2];
		if (eval1s[wLoop - 1] == 4 && wLoop > 0)
		{
			storeNote = centerCheck[eval1s[wLoop - 2]];
		}
		while (storeNote == eval1s[wLoop - 2] && wLoop > 1)
		{
			eval2 = Math.floor((Math.random()*10000) % 12);
			storeNote = spiralNote[eval1][eval2];
		}
		
			resObj.result = resObj.result + ","
			dataConvert(storeNote, resObj);
			timeAt = Math.trunc(Math.round(Number(startTime) + timeBetween * (wLoop)))
			resObj.result = resObj.result +  String(timeAt);
		eval1s[wLoop] = storeNote;
		eval1 = storeNote;

		eval2 = Math.floor((Math.random()*10000) % 12);
		wLoop++;
	}
}


function randomJump(eval1, eval2, storeNote, wLoop, noteNum, timeBetween, timeAt, eval1s, jumpNote, resObj, startTime)
{
	while (wLoop < noteNum)
	{
		storeNote = jumpNote[eval1][eval2];
		while (storeNote == eval1s[wLoop - 2] && wLoop > 1)
		{
			eval2 = Math.floor((Math.random()*10000) % 15);
			storeNote = jumpNote[eval1][eval2];
		}
	
			resObj.result = resObj.result + ","
			dataConvert(storeNote, resObj);
			timeAt = Math.trunc(Math.round(Number(startTime) + timeBetween * (wLoop)));
			resObj.result = resObj.result +  String(timeAt);
	eval1s[wLoop] = storeNote;
	eval1 = storeNote;

		eval2 = Math.floor((Math.random()*10000)% 15);
		wLoop++;
	}
}

function dataConvert(storeNote, result)
{
	let data1 = [0,0,0,1,1,1,2,2,2]
	let data2 = [0,1,2,0,1,2,0,1,2]
	resObj.result = resObj.result + String(data1[storeNote])  + "|" + String(data2[storeNote]) + "|"
}

document.getElementById("myButton").onclick = function(){

    bpm = document.getElementById("bpmValue").value
    divisor = document.getElementById("divisorValue").value
    length = document.getElementById("timeValue").value
	startTime = document.getElementById("startValue").value
	audioID = document.getElementById("audioValue").value
	resObj.result = String(audioID)
    noteNum = (bpm*divisor*length)/60
    timeBetween = (length * 1000) / noteNum
    eval1 = Math.floor((Math.random()*10000)%9)
    
	while (eval1 == 4)
    {
        eval1 = Math.floor((Math.random()*10000)%9)
    } 

    if (document.getElementById("jump").checked == true)
    {
		eval2 = Math.floor((Math.random()*10000)% 15)
		randomJump(eval1, eval2, storeNote, wLoop, noteNum, timeBetween, timeAt, eval1s, jumpNote, resObj, startTime)
    }

    else
    {
		eval2 = Math.floor((Math.random()*10000) % 12)
		randomSpiral( eval1, eval2, storeNote, wLoop, noteNum, timeBetween, timeAt, eval1s, spiralNote, resObj, startTime)
    }

	document.getElementById("resultText").innerHTML = resObj.result

}
