<?php /* 1.4 */ ?>

<div class="block feed index">

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

	<?php if ($user->user_type == 'child') { ?>

		<?php if (in_array('can_make_friends', $user->roles)) { ?>

			<div class="header">

				<div class="section">
					<h2>Friend Feed</h2>
				</div>

			</div>

			<div class="content">

				<div class="section friend-feed">
					<div class="items">
						<div class="scroll jscrolldiv">
  						
  						<?php /*
							<?php foreach ($data->items->group2 as $item) { ?>
								<div class="item">
									<span class="image">
										<img height="42" src="<?php print $item->src; ?>" width="42" />
									</span>
									<?php
										$_excerpt = $item->excerpt;
										$_excerpt = str_replace('/user/'.$user->uid, '/user', $_excerpt);
										$_excerpt = preg_replace('/("\/user\/)([0-9]+)(")/i', '/user/'.$user->uid.'/friends/$2/', $_excerpt);
									?>
									<span class="message">
										<?php print $_excerpt; ?>
									</span>
								</div>
							<?php } ?>
							
							<?php */?>
						</div>
					</div>

				</div>
			
			</div>

		<?php } ?>

	<?php } ?>

	<?php if (in_array('can_receive_notices', $user->roles) && sizeof($data->items->group1 ) > 0) { ?>

		<div class="header">

			<div class="section">
				<h2>Flip Feed</h2>
			</div>

		</div>

		<div class="content">

				<div class="section">
					<div class="items">
						<div class="scroll">
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
						</div>
					</div>

			</div>
		
		</div>

	<?php } ?>

</div>