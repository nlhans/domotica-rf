var stopUpdate = 0;

var updateData = function()
{
	if (stopUpdate != 0) return;
	
	var p = jsonPath + "sys.rtos";
	$.ajax({
		url: p,
		dataType: "json",
		
		success: function(data, textStatus, jqXHR)
		{
			var uptimeTxt = "";
			var uptimeSecs = data.uptime/1000;
			
			// Days
			if (data.uptime > 86400) uptimeTxt = Math.floor(uptimeSecs/86400) + " days";
			uptimeSecs = uptimeSecs % 86400;
			if (uptimeSecs != 0) uptimeTxt = uptimeTxt + ", ";
			
			// Hours
			if (data.uptime > 3600) uptimeTxt = uptimeTxt + Math.floor(uptimeSecs/3600) + " hours";
			uptimeSecs = uptimeSecs % 3600;
			if (uptimeSecs != 0) uptimeTxt = uptimeTxt + ", ";
			
			// Minutes
			if (data.uptime > 60) uptimeTxt = uptimeTxt + Math.floor(uptimeSecs/60) + " minutes";
			uptimeSecs = uptimeSecs % 60;
			if (uptimeSecs != 0) uptimeTxt = uptimeTxt + ", ";
			
			// Seconds
			if (data.uptime > 0) uptimeTxt = uptimeTxt + Math.floor(uptimeSecs) + " seconds";
			
			$('#uptime').html(uptimeTxt);
			
			// Add all tasks
			for (var task = 0; task < data.tasks.length; task++)
			{
				var t = data.tasks[task];
				
				//
				if ($('#task'+task).length == 0)
				{
					$('#tasks').append("<tr id='task"+task+"'></tr>");
				}
				
				var nextRun = t.time[2] - data.uptime;
				if (t.time[2] == 0) nextRun = "none";
				else if (nextRun == 0) nextRun = "now";
				else if (nextRun < 0) nextRun = "overdue";
				
				var lastRun = data.uptime - t.time[1];
				if (lastRun == 0) lastRun = "now";
				else if (lastRun < 0) lastRun = "error";
				
				var cpuLoad = Math.round(t.time[0]*100 *1000/ data.uptime)/1000.0;
				
				$('#task'+task).html("<td>"+task+"</td><td>"+t.priority+"</td><td>"+ t.name + "</td><td>" + t.state +"</td><td><div id='task_st_cur"+task+"' label='" + t.stack[0] + " / " + t.stack[2] + "'></div><div id='task_st_peak"+task+"' label='"+ t.stack[1] + " / " + t.stack[2] + "'></div>"+t.stack[0]+" /  "+t.stack[1]+" / " + t.stack[2] + "</td><td>Next run in " + nextRun + "<br/>Last run " + lastRun + "</td><td>" + t.events[0] + " / " + t.events[1] + "</td><td> " + cpuLoad + "%</td>");

				$('#task_st_cur'+task).progressbar({ value: t.stack[0], max: t.stack[2] } );
				$('#task_st_peak'+task).progressbar({ value: t.stack[1], max: t.stack[2] } );
				
				$('#task_st_cur'+task).css('max-height','12px');
				$('#task_st_peak'+task).css('max-height','12px');
			}

			
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
	setInterval(updateData, 1500);
});
