<!DOCTYPE html>
<html>
<head>
<meta content="text/html; charset=UTF-8"http-equiv=Content-Type>
<meta content="width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no"name=viewport>
<link href=/assets/logo.png rel="shortcut icon">
<link href=https://cdnjs.cloudflare.com/ajax/libs/materialize/0.98.2/css/materialize.min.css rel=stylesheet>
<style media=screen,projection rel=stylesheet>nav{background-color:#8e4585}</style>
<meta content="width=device-width,initial-scale=1"name=viewport>
<title>Select DATA.CSV for Analysis</title>
</head><body>
<nav>
   <div class=nav-wrapper>
      <ul class="hide-on-med-and-down left">
         <li class="active"><a href=#!>Electrical Performance Analysis</a></li>
         <li><a href=./sample/DATA.CSV> Download Sample CSV</a></li>
      </ul>
      <ul class=side-nav id=slide-out>
         <li><a href=#!>Electrical Performance Analysis</a>
		 <li><a href=./sample/DATA.CSV> Download Sample CSV</a></li>
      </ul>
      <a href=# class=button-collapse data-activates=slide-out><i class="fontsize mdi-navigation">Menu</i></a>
   </div>
</nav>
<div class=container style=text-align:center>
<h5>Select DATA.CSV obtained from SD card:</h5>
<form action="upload.php" method="post" enctype="multipart/form-data">
    <div class="file-field input-field">
      <div class="btn">
        <span>File</span>
    <input type="file" name="fileToUpload" id="fileToUpload">
      </div>
      <div class="file-path-wrapper">
        <input class="file-path validate" type="text">
      </div>
    </div>
<button class="btn waves-effect waves-red" type="submit" name="submit" value="Upload">Upload</button>
  </form>
</div>
<script src=https://code.jquery.com/jquery-2.1.1.min.js></script><script src=https://cdnjs.cloudflare.com/ajax/libs/materialize/0.98.2/js/materialize.min.js></script>
<script>$(".button-collapse").sideNav();</script>
</body>
</html>