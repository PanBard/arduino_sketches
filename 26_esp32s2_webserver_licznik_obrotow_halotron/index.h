const char MAIN_page[] PROGMEM = R"=====(














<!DOCTYPE html>
<html>
<style>
body{
  background: #808080;
  font-family: "Lucida Console", "Courier New", monospace;
}
.display{
    width: 400px;
     min-height: 250px;
     background: #404040;
     padding: 30px;
     box-sizing: border-box;
     color: #FFF;
     margin:20px;
     box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
     display:block;}
.hide{
	display:none;
}
.button_style{
 	background: #999999;
 	border-radius: 10px;
 	width: 90px;
	height: 50px;
}
.active_button_style{
	 background: #999999;
 	border-radius: 10px;
 	width: 90px;
 	height: 50px;
 	border: 2px solid green;
}
.sender_button_style{
	 background: #999999;
 	border-radius: 10px;
 	width: 80px;
 	height: 30px;
    margin: 2px;
}
#element_2{
 	background: #4d4d4d;
}

#element_404{
	 width: 400px;
     height: 50px;
     background: #404040;
     padding: 30px;
     box-sizing: border-box;
     color: #FFF;
     margin:20px;
     box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
     display:block;
     display: flex;
    flex-direction: row;
    justify-content: space-between;
    align-items: center;
}
#row{
    display: flex;
    flex-direction: row;
    justify-content: space-between;
    align-items: center;
}
div.ex3 {
  	background-color:#595959;
  	//width: 500px;
  height: 300px;
  overflow: auto;
  padding: 5px;
}
div.ex3 > p{
	background-color: #404040;
	padding: 1px;
	padding-left: 10px;
    margin: 3px;
}
#co{
	border: 2px solid black;
 	background: #404040;
    color: #FFF;
    padding: 10px;
}
input {
  	width: 100%;
  	margin: 2px;
}

</style>



<body>

<div id="co">
	<div id="row" > 
        <h2>LICZNK</h2>

	</div>
    
    <div id="row" >
      <h4>Liczba obrotów: <h1><span id="counter">0</span><h1> </h4><br>
      <div>
      		<h4>Connected devices: <span id="connected">0</span> </h4>
      		<h4>Runtime: <span id="time">0</span> </h4>
      </div>
	</div>
    
    

	<div id="row" >
        <button class="sender_button_style"  type="button" onclick="sendMessage()">RESET</button>
        
	</div>
   
	
</div>



<br><br>

<!--
<button class="button_style" type="button"onclick="addElement(342,1)">Add</button>
<button class="button_style" type="button"onclick="clearConsole()">remove</button>
-->

  <script>
  kopo = true;
  
function sendMessage(){
  	fetch("post", {
  		method: "POST",
  		body: JSON.stringify( {message: "reset"} ),
        headers: { "Content-type": "application/json; charset=UTF-8"}
        });
}
  
function clearConsole() {
  	const element = document.getElementById("console");
	element.innerHTML = '';
}

function changeBandwidthButtonsColors(number){
 	const array3 = [125,250,500];
    array3.forEach((element) => document.getElementById(element).className = "button_style");
	 switch (number) {
  case 125:
    document.getElementById(number).className = "active_button_style";
    break;
  case 250:
    document.getElementById(number).className = "active_button_style";
    break;
  case 500:
    document.getElementById(number).className = "active_button_style";
    break;
  default:
  	array3.forEach((element) => document.getElementById(element).className = "button_style");
   	break;
	}
}
  
function changePowerButtonsColors(number){
	const array2 = [17, 19, 20];
	array2.forEach((element) => document.getElementById(element).className = "button_style");
	 switch (number) {
  case 17:
    document.getElementById(number).className = "active_button_style";
    break;
  case 19:
    document.getElementById(number).className = "active_button_style";
    break;
  case 20:
    document.getElementById(number).className = "active_button_style";
    break;
  default:
  	array2.forEach((element) => document.getElementById(element).className = "button_style");
   	break;
	}
}
  
function autoScroll(){
  	if(kopo){
    kopo = false;
    document.getElementById("autoScroll").innerHTML = "Autoscroll OFF";
    }
    else{
    kopo = true;
    document.getElementById("autoScroll").innerHTML = "Autoscroll ON";
    }
}
  
function addElement(mes,nr){
  	const para = document.createElement("p");
    para.id = "record";
	const node = document.createTextNode("< "+nr.toString()+" >   "+mes.toString());
	para.appendChild(node);
	const element = document.getElementById("console");
	element.appendChild(para);
    if(kopo){
        var objDiv = document.getElementById("console");
  		objDiv.scrollTop = objDiv.scrollHeight;
        }
}
  
  
function buttonFunction() {
   if(document.getElementById("element_1").className == "display"){
   		document.getElementById("element_1").className = "hide";
   		document.getElementById("changer").innerHTML = "Settings";
        }
   else{
   		document.getElementById("element_1").className = "display";
   		document.getElementById("changer").innerHTML = "Hide Settings";
        }
}

function changeClass(mes){
	document.getElementById(mes).className = "active_button_style";
}

function postRequest(number){
	message = "";
	if(number == 17 || number == 19 || number == 20){
    	message = "Power["+number.toString()+"]" ;
    }
    else { message = "Bandwidth["+number.toString()+"E3]"; }
     fetch("post", {
  			method: "POST",
  			body: JSON.stringify({ message: message, title: "Fix my bugs", completed: false}),
  			headers: { "Content-type": "application/json; charset=UTF-8"}
            });
}

setInterval(
	function(){
        getData();
     }
    ,1000); //1000mSeconds update rate



function getData() {
  fetch("getData")
      .then(response => response.json())
      .then((json)=>{
      	document.getElementById("counter").innerHTML = json["counter"]
        document.getElementById("connected").innerHTML = json["connections"];
        document.getElementById("time").innerHTML = json["time"];
  		changeBandwidthButtonsColors(parseInt(json["bandwidth"]));
  		changePowerButtonsColors(parseInt(json["power"]));
      } )
}


  </script>

</body>
</html>


























)=====";