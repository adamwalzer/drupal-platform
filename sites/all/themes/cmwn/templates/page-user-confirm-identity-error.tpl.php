<?php require_once('modal/header.tpl.php'); ?>

	<div class="modal-inner-content step2 parent error" id="modal-inner-content">

		<h1>Sorry, We Can't Complete Your Registration Sign-Up</h1>

		<p>Our system may have detected inconsistent information entered in your registration form. Please remember to enter all information accurately.</p>
		<p>For more information visit our partner Lexis Nexis for more information about our site’s security requirments.</p>

		<div class="actions">
			<a class="modal-button" href="http://www.lexisnexis.com/privacy/for-consumers/request-personal-information.aspx" id="leaving-trigger" target="_parent">Learn More</a>
		</div>

	</div>

	<div class="block modal" id="leaving" style="display:none;">
		<div style="height:275px;width:420px;">
			<div class="section title">
				<h1>Are you sure you want to leave this site?</h1>
			</div>
			<div class="section buttons">
				<a class="modal-button leave" href="http://www.lexisnexis.com/privacy/for-consumers/request-personal-information.aspx" id="leaving-trigger" target="_parent">Yes</a>
				<a class="modal-button close" href="#">No Thanks</a>
			</div>
		</div>
	</div>

	<style>

		.block.modal .title {
			overflow:hidden;
		}

		.block.modal .title h1 {
			color:#FE5A27;
			font-family:'CMWNJadeRegular';
			font-size:44px;
			line-height:44px;
			margin:30px;
			padding:0px;
			text-transform: uppercase;
		}

		.block.modal .buttons .modal-button {
			bottom:30px;
		}

		.block.modal .buttons .modal-button.close {
			width:120px;
		}

		.block.modal .buttons .modal-button.leave {
			right:203px;
		}

	</style>

	<script>

		$(function(){

			jQuery.extend(Tipped.Skins,{
				'cmwn':{
					background:'#ffd7c7',
					border:{
						color:'#54c2f2',
						size:1
					},
					closeButtonSkin:'dark',
					radius:{
						size:6
					},
					shadow:{
						blur:12,
						color:'#000000',
						offset:{
							x:0,
							y:0
						},
						opacity:.06
					}
				}
			});

			var modal_leaving = $('#leaving');
			var modal_leaving_trigger = $('#leaving-trigger');

			if (modal_leaving.length == 1 && modal_leaving_trigger.length == 1) {
				modal_leaving_trigger.bind('click',function(){
					Tipped.create(
						'#modal-inner-content',
						modal_leaving.attr('id'),{
							'closeButton':false,
							'hideOn':false,
							'hook':{
				  				'target':'topmiddle',
				  				'tooltip':'topmiddle'
							},
							'inline':true,
							'onHide':function(){
								Tipped.remove('#modal-inner-content');
							},
							'skin':'cmwn',
							'stem':false
						}
					).show();
					return false;
				});
				modal_leaving.find('.modal-button.close').bind('click',function(){
					Tipped.remove('#modal-inner-content');
					return false;
				});
			}

		});

	</script>

<?php require_once('modal/footer.tpl.php'); ?>