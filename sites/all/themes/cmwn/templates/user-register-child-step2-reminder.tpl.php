<script>

	$(function(){

		modal.show(
			'/whats-my-story/my-interests/survey',[
				{'title':'<span>Step 1:</span> Enter your info'},
				{'title':'<span>Step 2:</span> Take the interest survey', 'href':'/whats-my-story/my-interests/survey'},
				{'title':'<span>Step 3:</span> Get your parent\'s approval'}
		]);

		modal.active(2,true);

	});

</script>