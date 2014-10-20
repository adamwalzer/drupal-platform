<div class="modal-registration-step-0">
	<a class="child" href="/user/register/child"></a>
	<a class="parent" href="/user/register/parent"></a>
	<a class="teacher" href="/user/register/teacher"></a>
</div>

<script type="text/javascript">
	$("#modal-content").hide();
	$(window).load(function() {
		$("#modal-content").fadeIn("slow",function() {
			$("#modal-content-inside").show();

			var thedelay = 0;
			$(".modal-registration-step-0 a img").each(function() {
				$(this).delay(thedelay).fadeTo("slow",1);
				thedelay += 300;
			});
 		});
	});
</script>