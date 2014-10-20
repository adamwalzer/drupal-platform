<script>

	$(function(){

		modal.show(
			'/user/register/parent/<?= $_SESSION['parent_token']; ?>/modal',[
				{'title':'<span>Step 1:</span> Enter Your Info','href':'/user/register/parent/<?= $_SESSION['parent_token']; ?>/modal'},
				{'title':'<span>Step 2:</span> Security Questions'},
				{'title':'<span>Step 3:</span> Add Your Child'}
		]);

		modal.active(1,true);

	});

</script>

<?php unset($_SESSION['parent_token']); ?>