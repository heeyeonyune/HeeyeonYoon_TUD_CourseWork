// Sign up
// show a message with a type of the input
function showMessage(input, message, type) {
	// get the small element and set the message
	const msg = input.parentNode.querySelector("small");
	msg.innerText = message;
	// update the class for the input
	input.className = type ? "success" : "error";
	return type;
}

function showError(input, message) {
	return showMessage(input, message, false);
}

function showSuccess(input) {
	return showMessage(input, "", true);
}

function hasValue(input, message) {
	if (input.value.trim() === "") {
		return showError(input, message);
	}
	return showSuccess(input);
}

function validateEmail(input, requiredMsg, invalidMsg) {
	// check if the value is not empty
	if (!hasValue(input, requiredMsg)) {
		return false;
	}
	// validate email format
	const emailRegex =
		/^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;

	const email = input.value.trim();
	if (!emailRegex.test(email)) {
		return showError(input, invalidMsg);
	}
	return true;
}

const form = document.querySelector("#signup");

const NAME_REQUIRED = "Please enter your name";
const EMAIL_REQUIRED = "Please enter your email";
const EMAIL_INVALID = "Please enter a correct email address format";

form.addEventListener("submit", function (event) {
	// stop form submission
	event.preventDefault();

	// validate the form
	let nameValid = hasValue(form.elements["name"], NAME_REQUIRED);
	let emailValid = validateEmail(form.elements["email"], EMAIL_REQUIRED, EMAIL_INVALID);
	// if valid, submit the form.
	if (nameValid && emailValid) {
		alert("Registration Successful!");
	}
});


// Clock (Current Korea time)
function updateClock() {
	// Adjust for Korea time (UTC+9)
	const now = new Date(new Date().getTime() + 9 * 60 * 60 * 1000);
	const hours = now.getHours().toString().padStart(2, '0');
	const minutes = now.getMinutes().toString().padStart(2, '0');
	const seconds = now.getSeconds().toString().padStart(2, '0');
	
	const timeString = `${hours}:${minutes}:${seconds}`;
	document.getElementById('clock').textContent = timeString;
  }

// Update the clock every second
 	setInterval(updateClock, 1000);

// Initial call to display the time immediately
  	updateClock();


// Modal _ service section
function openModal(type) {
	const modal = document.getElementById('modal');
	const modalContent = document.getElementById('modalContent');

	// content of the modal
	if (type === 'hours') {
	  modalContent.innerHTML = `
		<p>
		  <strong style="font-size: 1.2em;">Hours</strong><br>
		  Mon/Tue/Thu/Fri/Sun 10:00 ~ 18:00 <br>
		  Wed/Sat 10:00 ~ 21:00 <br>
		  <strong>* Entry closes 30 minutes before the closing time</strong>
		</p>
	  `;
	} else if (type === 'fare') {
	  modalContent.innerHTML = `
		<p>
		<strong style="font-size: 1.2em;">Free but Charges apply for special exhibitions</strong><br><br>
			- Effective January 18, 2022, the VACCINE PASS would not be required.<br>
			- Up to six people are allowed to be accompanied at the museum.
		</p>
		`;
	} else if (type === 'facility') {
	  modalContent.innerHTML = `
		<p>
			Click <a href="https://www.nmf.or.kr/enguser/sub/20181203184746590100_contents.do" target="_blank">here</a> to get the info.
		</p>
	  `;
	}

	// open the modal
	modal.style.display = 'block';
}

function closeModal() {
	document.getElementById('modal').style.display = 'none';
}

// exhibition button
function getDate1(){
    document.getElementById("message1").innerHTML = "Date: <br>Sep/23/2023 ~ Apr/25/2024 <br> Location: <br>Buncheong Ware and <br>White Porcelain Gallery 3F";
}
function getDate2(){
    document.getElementById("message2").innerHTML = "Date: <br>Sep/07/2023 ~ Dec/25/2023 <br> Location: <br> Calligraphy and PaintingⅡ";
}
function getDate3(){
    document.getElementById("message3").innerHTML = "Date: <br>Jul/22/2022 ~ Sep/29/2024 <br> Location: <br> World Art Gallery, <br>Permanent Exhibition Hall 3F";
}

// history (get info)

// Check if the element is found
function decade(){
	// Get the element using querySelector
	const decade_select = document.querySelector('.decade_select');
	// Code using getElementsByClassName
	// const decade_select = document.getElementsByClassName('decade_selector');

	if (decade_select) {
		decade_select.textContent = `You will receive information corresponding to that year.`;
	}
}
  



// Contact Us

function validateForm() {
	// retrieving form values
	let fname = document.getElementById("fname").value;
	let femail = document.getElementById("femail").value;
	let fmsg = document.getElementById("fmsg").value;

	// avoiding blank input
	if (fname == "" && femail == "" && fmsg == "") {
		alert("Name, email and message are required");
		return false;
	} else if (fname == "" && femail == "") {
		alert("Name and email are required");
		return false;
	} else if (fname == "" && fmsg == "") {
		alert("Name and message are required");
		return false;
	} else if (femail == "" && fmsg == "") {
		alert("Email and message are required");
		return false;
	} else if (fname == "") {
		alert("Name is required");
		return false;
	} else if (femail == "") {
		alert("Email is required");
		return false;
	} else if (fmsg == "") {
		alert("Message is required");
		return false;
	}

	// validating email format using a simple regular expression
	let emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
	if (!emailRegex.test(femail)) {
		alert("Please enter a valid email address");
		return false;
	}
	// if all validations pass
	return true;
}