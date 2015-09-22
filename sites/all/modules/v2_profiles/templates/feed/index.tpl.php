<?php /* 1.4 */ ?>

<div class="block feed sidebar-profile index">

	<?php if (in_array('can_receive_notices', $user->roles) && sizeof($data->items->group1 ) > 0) { ?>

		<div class="header">

			<div class="section">
				<h2>Live News</h2>
			</div>

		</div>

		<div class="content">

			<div class="section">
				<div class="items">
					<div class="scroll">
						<?php foreach ($data->items->group1 as $item) { ?>
							<div class="item">
								<span class="image">
									<img height="42" src="<?php print $item->src; ?>" width="42" />
								</span>
								<span class="message">
									<?php print $item->excerpt; ?>
								</span>
							</div>
						<?php } ?>
					</div>
				</div>

			</div>
		
		</div>

	<?php } ?>

	<?php if (in_array($user->user_type, array('child','teacher','parent'))) { ?>

		<?php if (in_array('can_make_friends', $user->roles)) { ?>
      <div class="sidebar-toggle hide"></div>
			<div class="header">
				<div class="section">
					<h2>Friend Feed</h2>
				</div>
			</div>
			<div class="content">
				<div class="section friend-feed">
					<div class="items">
						<div class="scroll jscrolldiv" u="<?php print $item->user->uid;?>">
						</div>
					</div>
				</div>
			</div>
		<?php } ?>

	<?php } ?>

	<?php if (in_array('can_receive_notices', $user->roles)) { ?>

		<div class="header">

			<div class="section">
				<h2>Flip Feed</h2>
			</div>

		</div>

		<div class="content">

				<div class="section flip-feed">
					<div class="items">
						<div class="scroll jscrolldiv">
  						<?php /*
							<?php foreach ($data->items->group3 as $item) { ?>
								<div class="item">
									<span class="image">
										<img height="42" src="<?php print $item->src; ?>" width="42" />
									</span>
									<span class="message">
										<?php print $item->excerpt; ?>
									</span>
								</div>
							<?php } ?>
							<?php */ ?>
						</div>
					</div>

			</div>
		
		</div>

	<?php } ?>

</div>