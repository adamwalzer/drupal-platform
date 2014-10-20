<?php /* 1.4 */ ?>

<?php if(isset($_SESSION['avatar_updated_pending_moderation'])) { unset($_SESSION['avatar_updated_pending_moderation']); ?>
	<div class="message-modal-underlay" id="message-modal-underlay">
		<div class="message-modal">
			<a href="#" class="close-message-modal x-close"></a>
			<div class="heading">Your new profile photo will be available soon!</div>
			<p>In the meantime this pre-post is available only for you to see.</p>
			<a href="#" class="close-message-modal button"><span>Continue</span></a>
		</div> <!-- /.message-modal -->
	</div> <!-- /.message-modal-underlay -->
	<script type="text/javascript">
		$("#v2").append($("#message-modal-underlay"));
		var theModal = $("#message-modal-underlay .message-modal");
		$(theModal).css({'margin-top': '-'+($(theModal).height()/2)+"px"});
		$(".close-message-modal").click(function() {
			$(".message-modal-underlay").fadeOut("slow",function() {
				$(this).remove();
			});
		});
	</script>
<?php } ?>

<div class="block shadow avatars index">
	<?php if ($data->user->uid != $user->uid) { ?>
		<div class="header">

			<div class="section">
				<h2><?php print $data->user->name; ?></h2>
			</div>

		</div>
	<?php } ?>

	<div class="content">

		<div class="section">
			<div class="image">
				<img alt="" height="216" src="<?php print $data->user->avatar; ?>" width="216" />
			</div>
			<div class="actions">
				<?php if ($data->user->uid == $user->uid) { ?>
					<?php if (in_array('can_upload_media', array_values($data->user->roles))) { ?>
						<a href="/user/<?php print $data->user->uid; ?>/avatars/add">Change Photo</a>
					<?php } else { ?>
						<a href="/user/<?php print $data->user->uid; ?>/avatars/browse">Change Photo</a>
					<?php } ?>
					&nbsp; | &nbsp;
					<a href="/user/<?php print $data->user->uid; ?>/account">Edit Profile</a>
				<?php } else if ($user->user_type == 'child' && in_array('can_make_friends', array_values($user->roles))) { ?>
					<?php $data->relationship = user_relationships_load(array('between' => array($user->uid, $data->user->uid))); $data->relationship = array_pop($data->relationship); ?>
					<?php if (!$data->relationship) { ?>
						<a class="button green small" href="/user/<?php print $user->uid; ?>/friends/<?php print $data->user->uid; ?>/add">Add Friend</a>
					<?php } else if ($data->relationship->approved == 0) { ?>
						<span class="button small disabled">Request Sent</span>
					<?php } ?>
				<?php } else if ($user->user_type == 'parent' && !arg(3)) { ?>
					<a class="button small" href="/user/<?php print $user->uid; ?>/children/<?php print $data->user->uid; ?>">View Full Profile</a>
				<?php } ?>
			</div>
		</div>

	</div>

</div>