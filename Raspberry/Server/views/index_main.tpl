<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <title>Welcome!</title>

    <link rel="stylesheet" type="text/css" href="/static/bootstrap.min.css">
    <link href="https://gitcdn.github.io/bootstrap-toggle/2.2.2/css/bootstrap-toggle.min.css" rel="stylesheet">
	<link rel="stylesheet" type="text/css" href="static/style.css"> 
    
    

    

</head>
<body>

<div class="container-fluid">
	<div class="row">
		<div id="qwerty" class="col-md-12">
			<h1 class="text-center text-primary">
				Smart Home control
			</h1>
		</div>
	</div>

	<div class="row">		
		<div class="col-md-2">
			<div class="nav flex-column nav-pills" id="v-pills-tab" role="tablist" aria-orientation="vertical">
	  			<a class="nav-link active" id="v-pills-bedroom-tab" data-toggle="pill" href="#v-pills-bedroom" role="tab" aria-controls="v-pills-bedroom" aria-selected="true">
	  				bedroom
	  			</a>

	  			<a class="nav-link" id="v-pills-kitchen-tab" data-toggle="pill" href="#v-pills-kitchen" role="tab" aria-controls="v-pills-kitchen" aria-selected="false">
	  				kitchen
	  			</a>

	  			<a class="nav-link" id="v-pills-living-tab" data-toggle="pill" href="#v-pills-living" role="tab" aria-controls="v-pills-living" aria-selected="false">
	  				living room
	  			</a>

	  			<a class="nav-link" id="v-pills-bathroom-tab" data-toggle="pill" href="#v-pills-bathroom" role="tab" aria-controls="v-pills-bathroom" aria-selected="false">
	  				bathroom
	  			</a>
	  		</div>
	  	</div>

	  	<div class="col-md-10">
			
		  	<div class="tab-content" id="v-pills-tabContent">
		  		% len_json = len(data) + 1

		  		<h1>Всього елементів в файлі {{len_json-1}}</h1>
			  	<div class="tab-pane fade show active" id="v-pills-bedroom" role="tabpanel" aria-labelledby="v-pills-home-tab">
			  		<div class="row">						
						%for j in range(1,len_json):
							%if data[str(j)]['room'] == "bedroom":
				  				<div class="col-md-3">
									<div class="jumbotron card card-block text-center" >
										<div id="{{data[str(j)]['id']}}">
											<h2> {{data[str(j)]['name']}}</h2>
											<h2> {{data[str(j)]['group']}} : {{data[str(j)]['id']}}</h2>
											<h3>Status: {{data[str(j)]['value']}}</h3>									
								
											%if data[str(j)]['value'] == 'Enable':
												<input type="checkbox" id="btn_socket_{{data[str(j)]['id']}}" checked data-toggle="toggle" data-onstyle="success" data-width="60%" data-offstyle="danger">
											%else:
												<input type="checkbox" id="btn_socket_{{data[str(j)]['id']}}" data-toggle="toggle" data-onstyle="success" data-offstyle="danger" data-width="60%">
											%end
										</div>
									</div>
								</div>		
							%end								
						%end					
					</div>
				</div>

				<div class="tab-pane fade" id="v-pills-kitchen" role="tabpanel" aria-labelledby="v-pills-kitchen-tab">					
					<div class="row">						
						%for j in range(1,len_json):
							%if data[str(j)]['room'] == "kitchen":
								<div class="col-md-3">
									<div class="jumbotron card card-block" >
										<div id="{{data[str(j)]['id']}}">
											<h2> {{data[str(j)]['name']}}</h2>
											<h2> {{data[str(j)]['group']}} : {{data[str(j)]['id']}}</h2>
											<h3>Status: {{data[str(j)]['value']}}</h3>									
										
											%if data[str(j)]['value'] == 'Enable':
												<input type="checkbox" id="btn_socket_{{data[str(j)]['id']}}" checked data-toggle="toggle" data-onstyle="success" data-offstyle="danger">
											%else:
												<input type="checkbox" id="btn_socket_{{data[str(j)]['id']}}" data-toggle="toggle" data-onstyle="success" data-offstyle="danger">
											%end
										</div>
									</div>
								</div>
							%end
						%end
					</div>
				</div>

				<div class="tab-pane fade" id="v-pills-living" role="tabpanel" aria-labelledby="v-pills-kitchen-tab">					
					<div class="row">						
						%for j in range(1,len_json):
							%if data[str(j)]['room'] == "living":
								<div class="col-md-3">
									<div class="jumbotron card card-block" >
										<div id="{{data[str(j)]['id']}}">
											<h2> {{data[str(j)]['name']}}</h2>
											<h2> {{data[str(j)]['group']}} : {{data[str(j)]['id']}}</h2>
											<h3>Status: {{data[str(j)]['value']}}</h3>									
										
											%if data[str(j)]['value'] == 'Enable':
												<input type="checkbox" id="btn_socket_{{data[str(j)]['id']}}" checked data-toggle="toggle" data-onstyle="success" data-offstyle="danger">
											%else:
												<input type="checkbox" id="btn_socket_{{data[str(j)]['id']}}" data-toggle="toggle" data-onstyle="success" data-offstyle="danger">
											%end
										</div>
									</div>
								</div>
							%end
						%end
					</div>
				</div>

				<div class="tab-pane fade" id="v-pills-bathroom" role="tabpanel" aria-labelledby="v-pills-kitchen-tab">					
					<div class="row">						
						%for j in range(1,len_json):
							%if data[str(j)]['room'] == "bathroom":
								<div class="col-md-3">
									<div class="jumbotron card card-block" >
										<div id="{{data[str(j)]['id']}}">
											<h2> {{data[str(j)]['name']}}</h2>
											<h2> {{data[str(j)]['group']}} : {{data[str(j)]['id']}}</h2>
											<h3>Status: {{data[str(j)]['value']}}</h3>									
										
											%if data[str(j)]['value'] == 'Enable':
												<input type="checkbox" id="btn_socket_{{data[str(j)]['id']}}" checked data-toggle="toggle" data-onstyle="success" data-offstyle="danger">
											%else:
												<input type="checkbox" id="btn_socket_{{data[str(j)]['id']}}" data-toggle="toggle" data-onstyle="success" data-offstyle="danger">
											%end
										</div>
									</div>
								</div>
							%end
						%end
					</div>
				</div>
			</div>
		</div>
	</div>
</div>

<script type="text/javascript" src="/static/jquery-3.3.1.js"></script>	
<script type="text/javascript" src="/static/bootstrap.min.js"></script>
<script src="https://gitcdn.github.io/bootstrap-toggle/2.2.2/js/bootstrap-toggle.min.js"></script>
<script type="text/javascript" src="/static/scripts.js"></script> 
    
</body>
</html>