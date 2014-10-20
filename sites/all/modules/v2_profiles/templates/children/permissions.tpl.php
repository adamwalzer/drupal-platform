<?php /* 1.4 */ ?>

<?php foreach ($data->items as $item) { ?>

	<div class="block shadow account index permissions">

		<div class="header">

			<div class="section">
				<h2><?php print $item->name; ?></h2>
			</div>

			<div class="section buttons">
				<form action="/user/<?php print $user->uid; ?>/children/<?php print $item->uid; ?>/delete" method="post">
					<input name="step" type="hidden" value="9" />
					<button class="button" data-modal="account-delete-<?php print $item->uid; ?>" type="submit">Delete This Profile</button>
				</form>
			</div>

		</div>

		<div class="content">

			<div class="section">
				<form action="" method="post">
					<fieldset class="items">
						<div class="item">
							<h3>Approve your child to upload images and videos.</h3>
						</div>
						<div class="item">
							<input<?php print (in_array('can_upload_media',$item->roles))? ' checked="checked"':''; ?> id="role11" name="can_upload_media" type="radio" value="1" />
							<label for="role11">Yes</label>
						</div>
						<div class="item">
							<input<?php print (in_array('can_upload_flip_media',$item->roles))? ' checked="checked"':''; ?> id="role12" name="can_upload_media" type="radio" value="2" />
							<label for="role12">Yes, but only to complete action items</label>
						</div>
						<div class="item">
							<input<?php print (!in_array('can_upload_media',$item->roles) && !in_array('can_upload_flip_media',$item->roles))? ' checked="checked"':''; ?> id="role13" name="can_upload_media" type="radio" value="0" />
							<label for="role13">No</label>
						</div>
					</fieldset>
					<fieldset class="items">
						<div class="item">
							<h3>Approve your child to make friends.</h3>
						</div>
						<div class="item">
							<input<?php print (in_array('can_make_friends',$item->roles))? ' checked="checked"':''; ?> id="role21" name="can_make_friends" type="radio" value="1" />
							<label for="role21">Yes</label>
						</div>
						<div class="item">
							<input<?php print (!in_array('can_make_friends',$item->roles))? ' checked="checked"':''; ?> id="role22" name="can_make_friends" type="radio" value="0" />
							<label for="role22">No</label>
						</div>
					</fieldset>
					<fieldset class="items">
						<div class="item">
							<h3>Approve Change My World Now to send notices to your child.</h3>
						</div>
						<div class="item">
							<input<?php print (in_array('can_receive_notices',$item->roles))? ' checked="checked"':''; ?> id="role31" name="can_receive_notices" type="radio" value="1" />
							<label for="role31">Yes</label>
						</div>
						<div class="item">
							<input<?php print (in_array('can_receive_notices_via_parent',$item->roles))? ' checked="checked"':''; ?> id="role32" name="can_receive_notices" type="radio" value="2" />
							<label for="role32">Yes, but CC me on the notices</label>
						</div>
						<div class="item">
							<input<?php print (!in_array('can_receive_notices',$item->roles) && !in_array('can_receive_notices_via_parent',$item->roles))? ' checked="checked"':''; ?> id="role33" name="can_receive_notices" type="radio" value="0" />
							<label for="role33">No</label>
						</div>
					</fieldset>
					<input name="uid" type="hidden" value="<?php print $item->uid; ?>" />
					<button class="button" type="submit">Save</button>
				</form>
			</div>

		</div>

	</div>

	<div class="block modal" id="account-delete-<?php print $item->uid; ?>" style="display:none;">
		<div class="section title">
			<h1>Are you sure you want to delete this profile?</h1>
		</div>
		<div class="section cms">
			<p>Deleting this profile will erase this account and all of it's personal information permanently.</p>
		</div>
		<div class="section buttons">
			<form action="/user/<?php print $user->uid; ?>/children/<?php print $item->uid; ?>/delete" method="post">
				<button class="button" type="submit">Yes, Delete This Profile</button>
				<button class="button primary" type="button">No, Keep This Profile Active</button>
			</form>
		</div>
	</div>

<?php } ?>