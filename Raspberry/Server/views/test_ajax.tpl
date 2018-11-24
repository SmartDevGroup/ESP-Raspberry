<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <title>Welcome!</title>

   	<script type="text/javascript" src="/static/jquery-3.3.1.js"></script>
    <script type="text/javascript">
    // Магія розпочнеться лише після повного завантаження сторінки
    $(document).ready(function(){
        // Посилання з id="test" буде тригером події
        $("#test").click(function() {
            // AJAX-запит на потрібну адресу
            $.get("/ajax_test/", function(data) {
                // Замінюємо текст тегу з id="target" на отримані дані
                $("#target").html(data.param1+' '+data.param2);
            });
        });
    });
	</script>   

</head>
<body> 
	
	<!-- Елемент що активує процес -->
	<a id="test" href="javascript:">Натисни мене ніжно</a>

	<!-- Елемент, текст якого буде змінено -->
	<div id="target">Я готовий до змін.</div>
	

	
	
    
  </body>
</html>