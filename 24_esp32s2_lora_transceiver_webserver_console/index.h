const char MAIN_page[] PROGMEM = R"=====(



<!DOCTYPE html>
<html>
<style>
body{
  background: #808080;
  font-family: "Lucida Console", "Courier New", monospace;
}
.button_style{
 	background: #999999;
 	border-radius: 10px;
 	width: 90px;
	height: 50px;
}
.sender_button_style{
	 background: #999999;
 	border-radius: 10px;
 	width: 80px;
 	height: 30px;
    margin: 2px;
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
        <h2>LoRa Console</h2>
        <button id="autoScroll" class="button_style" type="button"onclick="autoScroll()">autoscroll ON</button>
	</div>
    <div id="console" class="ex3"> </div>
	<div id="row" >
        <button class="sender_button_style"  type="button" onclick="sendMessage()">Send</button>
        <input type="text" id="message_input" name="lname" >        
	</div>
   
	<div id="row" >
      <h4>Received packets: <span id="counter">0</span> </h4><br>
      <div>
      		<h4>Connected devices: <span id="connected">0</span> </h4>
      		<h4>Runtime: <span id="time">0</span> </h4>
      </div>
	</div>
</div>

  <script>
  kopo = true;
  
function sendMessage(){
  	LoRaMessage = "";
  	LoRaMessage = document.getElementById('message_input').value;
  	fetch("loraMessageSender", {
  		method: "POST",
  		body: JSON.stringify( {message: LoRaMessage} ),
        headers: { "Content-type": "application/json; charset=UTF-8"}
        });
}
  
function clearConsole() {
  	const element = document.getElementById("console");
	element.innerHTML = '';
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
  
setInterval(
	function(){
        getLog();
        getData();
     }
    ,1000); //1000mSeconds update rate

function getLog(){
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function(){
        if (this.readyState == 4 && this.status == 200){
          originalString = this.responseText;
            separatedArray = [];
       		separatedArray = originalString.split('\n');
            clearConsole();
            for (let i = 0; i < separatedArray.length; i++) {
            		if(separatedArray[i] != "\n"){
                    	addElement(separatedArray[i],i+1);
                    }
  			}                     
        }
      }
      xhttp.open("GET", "readLoraLogs", true);
      xhttp.send();
}

function getData() {
  fetch("getData")
      .then(response => response.json())
      .then((json)=>{
      	document.getElementById("counter").innerHTML = json["counter"]
        document.getElementById("connected").innerHTML = json["connections"];
        document.getElementById("time").innerHTML = json["time"];
      } )
}
  </script>
</body>
</html>




)=====";