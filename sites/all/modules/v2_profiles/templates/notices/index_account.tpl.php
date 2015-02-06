<?php /* 1.4 */ ?>

<?php if ($data->user->user_type == 'child') { ?>

	<?php print v2_profiles_flips_index($data->user->uid); ?>

<?php } ?>

<div class="block shadow notices index">

	<div class="header">

		<div class="section">
			<h2>Account Notices</h2>
		</div>

	</div>

	<div class="content">

		<div class="section">
			<div class="empty">
				<?php
  				print cmwn_notifications_messaging_get($data->user,'Password Changed');
  				print cmwn_notifications_messaging_get($data->user,'Username Changed');  				
  				print cmwn_notifications_messaging_get($data->user,'Email Changed');
				?>
			</div>
		</div>

	</div>

</div>