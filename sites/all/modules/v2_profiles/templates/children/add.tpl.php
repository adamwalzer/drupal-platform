<?php /* 1.4 */ ?>

<?php if(!isset($_SESSION['cptoken'])) : ?>
<div id="add-child-overlay">
	<div class="add-child-underlay"></div>
	<div class="add-child-overlay">
		<h3>Please log out and have your child sign up using your email address.</h3>
		<a href="/logout" class="button green">Log Out</a>
	</div> <!-- /.add-child-overlay -->
</div>
<script type="text/javascript">
$().ready(function() {
	$("#v2").prepend($("#add-child-overlay"));
});
</script>
<?php
else :
	$cptoken = $_SESSION['cptoken'];
	unset($_SESSION['cptoken']);

endif;
?>

<div class="block shadow account permissions">

	<div class="header">

		<div class="section">
			<h2>Add a Child</h2>
		</div>

	</div>

	<div class="content">

		<div class="section">
			<form action="" enctype="multipart/form-data" method="post">
				<fieldset class="items">
					<div class="item">
						<h3>Enter the token you received in your reminder email.</h3>
					</div>
					<div class="item">
						<input name="token" type="text" value="<?php echo (isset($cptoken)?$cptoken:'');?>" />
					</div>
				</fieldset>
				<button class="button" type="submit">Submit</button>
			</form>
		</div>

	</div>

</div>