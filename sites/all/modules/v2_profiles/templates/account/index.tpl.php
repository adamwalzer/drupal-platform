<?php /* 1.4 */ ?>

<div class="block shadow account index">

	<div class="header">

		<div class="section">
			<h2>Edit Password</h2>
		</div>

		<div class="section buttons">
			<form action="" method="post">
				<input name="step" type="hidden" value="9" />
				<button class="button" data-modal="account-delete" type="submit">Delete This Profile</button>
			</form>
		</div>

	</div>

	<div class="content">

		<div class="section">
			<form action="" method="post">
				<fieldset class="items">
					<div class="item">
						<input name="password1" placeholder="Change your current password" type="password" />
					</div>
					<div class="item">
						<input name="password2" placeholder="Confirm your new password" type="password" />
					</div>
				</fieldset>
				<input name="step" type="hidden" value="1" />
				<button class="button" type="submit">Save</button>
			</form>
		</div>

	</div>

</div>

<div class="block shadow account index">

	<div class="header">

		<div class="section">
			<h2>Edit Email</h2>
		</div>

	</div>

	<div class="content">

		<div class="section">
			<form action="" method="post">
				<fieldset class="items">
					<div class="item">
						<input name="email" placeholder="Email Address" type="text" value="<?php print htmlspecialchars($data->form->email); ?>" />
					</div>
				</fieldset>
				<input name="step" type="hidden" value="2" />
				<button class="button" type="submit">Save</button>
			</form>
		</div>

	</div>

</div>

<div class="block shadow account index">

	<div class="header">

		<div class="section">
			<h2>Edit Personal Information</h2>
		</div>

	</div>

	<div class="content">

		<div class="section">
			<form action="" method="post">
				<fieldset class="items">
					<div class="item">
						<input name="first_name" placeholder="First Name" type="text" value="<?php print htmlspecialchars($data->form->first_name); ?>" />
					</div>
					<div class="item">
						<input name="last_name" placeholder="Last Name" type="text" value="<?php print htmlspecialchars($data->form->last_name); ?>" />
					</div>
				</fieldset>
				<input name="step" type="hidden" value="3" />
				<button class="button" type="submit">Save</button>
			</form>
		</div>

	</div>

</div>

<div class="block shadow account index">

	<div class="header">

		<div class="section">
			<h2>Edit Username</h2>
		</div>

	</div>

	<div class="content">

		<div class="section">
			<form action="" method="post">
				<fieldset class="items">
					<div class="item">
						<input name="username" placeholder="Username" type="text" value="<?php print htmlspecialchars($data->form->username); ?>" />
					</div>
				</fieldset>
				<input name="step" type="hidden" value="4" />
				<button class="button" type="submit">Save</button>
			</form>
		</div>

	</div>

</div>

<div class="block modal" id="account-delete" style="display:none;">
	<div class="section title">
		<h1>Are you sure you want to delete this profile?</h1>
	</div>
	<div class="section cms">
		<p>Deleting this profile will erase this account and all of it's personal information permanently.</p>
	</div>
	<div class="section buttons">
		<form action="" method="post">
			<input name="step" type="hidden" value="9" />
			<button class="button" type="submit">Yes, Delete This Profile</button>
			<button class="button primary" type="button">No, Keep This Profile Active</button>
		</form>
	</div>
</div>