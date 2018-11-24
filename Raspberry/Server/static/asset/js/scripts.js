// Empty JS for your own code to be here
 $(document).ready(function(){
 	$('input[type="checkbox"]').change(function() {
 		var btn_id = this.id;
 		var arr = btn_id.split('_');
 		if ($(this).prop('checked') == true){
 		 	chek_ajax(arr[2],'Enable');
      send_to_controller('Enable');
 		}else {
 		 	chek_ajax(arr[2],'Disable');
      send_to_controller('Disable');
 		}
 	});
});

function chek_ajax(id,status){
	$.ajax({
		url: '/chek_box_ajax',
		type: 'GET',
		data:'obj_id=' + id + '&obj_status=' + status,
		success: function(data) {
			$('div#'+id+' > h3').html('Status: '+data);
		},
    });
}

function send_to_controller(status_var){
	var url = "http://192.168.31.50?status="+status_var;

  $.get(url);
}
