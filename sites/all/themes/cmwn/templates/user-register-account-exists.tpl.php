<div id="account-exists">
	<div style="height:210px;width:360px;">
		<h1>This account is already active!</h1>
		<p><a class="modal-button" href="/">Close and Log In</a></p>
	</div>
</div>

<style>

	#account-exists h1 {
		color:#54c2f2;
		font-family:'CMWNJadeRegular';
		font-size:48px;
		font-weight:normal;
		line-height:48px;
		margin:24px;
	}

	#account-exists .modal-button {
		bottom:24px;
		color:#ffffff;
		padding:0px;
		right:60px;
		text-align:center;
		width:240px;
	}

	#account-exists .modal-button:hover {
		color:#7a29bd;
	}

</style>

<script>

	$(function(){

		Processing.show();

		$('#processing').append('<div id="modal" style="height:240px;margin:0px auto;" />');

		Tipped.create(
			'#modal',
			'account-exists',{
				'closeButton':false,
				'hideOn':false,
				'inline':true,
				'skin':'cmwn',
				'stem':false
			}
		).show();

	});

</script>

<?php unset($_SESSION['parent_token']); ?>