
var stopUpdate = 0;

var updateData = function()
{
	if (stopUpdate != 0) return;
	
	var p = jsonPath + "index";
	$.ajax({
		url: p,
		dataType: "json",
		
		success: function(data, textStatus, jqXHR)
		{
			$('#name').html(data.name);
			
			$('#upstairs_temperature').html(data.data.upstairs.temperature + "C");
			$('#upstairs_humidity').html(data.data.upstairs.humidity + "%");
			
			$('#downstairs_temperature').html(data.data.downstairs.temperature + "C");
			$('#downstairs_humidity').html(data.data.downstairs.humidity + "%");
			
			$('#scullery_temperature').html(data.data.scullery.temperature + "C");
			$('#scullery_humidity').html(data.data.scullery.humidity + "%");

			$('#status').html('Lovely');
		},
		error: function(jqXHR, textStatus, errorThrown)
		{
			$('#status').html('JSON backend fail: ' + errorThrown);
			stopUpdate++;
		}
	});
}

updateData();

$(function() {
	setInterval(updateData, 500);
});
