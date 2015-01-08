<?php
  
global $cmwn_feed_menu_items;
$cmwn_feed_menu_items['cmwn_feed/friend'] = array(
  'page callback' => 'cmwn_friend_feed',
  'access arguments' => array('access content'),
  'type' => MENU_CALLBACK,
);
  
function cmwn_friend_feed_queries_list(){
  $feed_queries = array(
    'friend request',
    'completes flip milestone',
    'signs up flip',
    'completes flip'
  );  
}
  
function cmwn_friend_feed($uid = 0, $page = 0) {//ganked/modified from feed.inc in v2 profile
    
		$items = array();
    global $user;
    global $feed_queries;
    
		$friend_feed_user = user_load($uid);

		if (!$friend_feed_user || $user->uid != $uid){
  		print '';
  		exit();
		} 		

		//Friend feed - find all this person's friends first!
		$query = "SELECT requester_id as friend_uid FROM {user_relationships} WHERE requestee_id = %d and approved =1 order by updated_at desc";
		
		$results = db_query($query, $uid);

    $friends = array();
    
		while ($result = db_fetch_object($results)) {
      $friends[] = $result->friend_uid;
		}
    
    $friend_uid_placeholders = db_placeholders($friends);
		
		$query_union = '';
		
    $feed_queries['friend request'] = array(
      	'query' => "SELECT CONCAT('<a href=\"/user/', user_a.uid,'\">',user_a.name,'</a> has become friends with <a href=\"/user/',user_b.uid, '\">', user_b.name, '</a>') as excerpt, user_a.uid as uid, updated_at as stamp,
        
        CASE 
          WHEN FROM_UNIXTIME(updated_at) between date_sub(now(), INTERVAL 60 minute) and now() THEN concat(minute(TIMEDIFF(now(), FROM_UNIXTIME(updated_at))), ' minutes ago')
          WHEN datediff(now(), FROM_UNIXTIME(updated_at)) = 1 THEN 'Yesterday'
          WHEN FROM_UNIXTIME(updated_at) between date_sub(now(), INTERVAL 48 hour) and now() THEN concat(hour(TIMEDIFF(NOW(), FROM_UNIXTIME(updated_at))), ' hours ago')
        ELSE date_format(FROM_UNIXTIME(updated_at), '%a, %m/%%d/%y')
        END      	as time_ago
      	
      	
 FROM {user_relationships} ur join {users} user_a on ur.requester_id = user_a.uid join {users} user_b on user_b.uid = ur.requestee_id WHERE requester_id in($friend_uid_placeholders) and approved = 1 UNION ALL ",
      );
      
      $feed_queries['completes flip milestone'] = array(
      	'query' => "SELECT CONCAT('<a href=\"/user/', u.uid,'\">',u.name,'</a> has completed the action item milestone \"<em>', n.title ,'</em>.\"') as excerpt, ws.uid as uid, submitted as stamp,
      
        
        CASE 
          WHEN FROM_UNIXTIME(submitted) between date_sub(now(), INTERVAL 60 minute) and now() THEN concat(minute(TIMEDIFF(now(), FROM_UNIXTIME(submitted))), ' minutes ago')
          WHEN datediff(now(), FROM_UNIXTIME(submitted)) = 1 THEN 'Yesterday'
          WHEN FROM_UNIXTIME(submitted) between date_sub(now(), INTERVAL 24 hour) and now() THEN concat(hour(TIMEDIFF(NOW(), FROM_UNIXTIME(submitted))), ' hours ago')
        ELSE date_format(FROM_UNIXTIME(submitted), '%a, %m/%%d/%y')
        END      	as time_ago

        
        FROM {webform_submissions} ws JOIN {node} n on n.nid = ws.nid join {users} u on u.uid = ws.uid and n.type='action' WHERE ws.uid in($friend_uid_placeholders) UNION ALL ",
      );
      
      $feed_queries['signs up flip'] = array(
      	'query' => "select CONCAT('<a href=\"/user/', u.uid,'\">',u.name,'</a> has begun the action item \"<em>', nf.title ,'</em>.\"') as excerpt, ws.uid as uid, ws.submitted as stamp,
      
        CASE 
          WHEN FROM_UNIXTIME(ws.submitted) between date_sub(now(), INTERVAL 60 minute) and now() THEN concat(minute(TIMEDIFF(now(), FROM_UNIXTIME(ws.submitted))), ' minutes ago')
          WHEN datediff(now(), FROM_UNIXTIME(ws.submitted)) = 1 THEN 'Yesterday'
          WHEN FROM_UNIXTIME(ws.submitted) between date_sub(now(), INTERVAL 48 hour) and now() THEN concat(hour(TIMEDIFF(NOW(), FROM_UNIXTIME(ws.submitted))), ' hours ago')
        ELSE date_format(FROM_UNIXTIME(ws.submitted), '%a, %m/%%d/%y')
        END      	as time_ago

        
         from {webform_submissions} ws join node na on ws.nid = na.nid join {content_field_actions} cfa on cfa.field_actions_nid = na.nid join {node} nf on nf.nid = cfa.nid join {users} u on u.uid = ws.uid where ws.uid in($friend_uid_placeholders) and cfa.delta = (select min(delta) from {content_field_actions} cfai where cfai.nid = nf.nid)  UNION ALL ",
      );
      
      $feed_queries['completes flip'] = array(
      	'query' => "select CONCAT('<a href=\"/user/', u.uid,'\">',u.name,'</a> has completed the action item \"<em>', nf.title ,'</em>.\"') as excerpt, ws.uid as uid, ws.submitted as stamp,
      	
        
        CASE 
          WHEN FROM_UNIXTIME(ws.submitted) between date_sub(now(), INTERVAL 60 minute) and now() THEN concat(minute(TIMEDIFF(now(), FROM_UNIXTIME(ws.submitted))), ' minutes ago')
          WHEN datediff(now(), FROM_UNIXTIME(ws.submitted)) = 1 THEN 'Yesterday'
          WHEN FROM_UNIXTIME(ws.submitted) between date_sub(now(), INTERVAL 48 hour) and now() THEN concat(hour(TIMEDIFF(NOW(), FROM_UNIXTIME(ws.submitted))), ' hours ago')
        ELSE date_format(FROM_UNIXTIME(ws.submitted), '%a, %m/%%d/%y')
        END      	as time_ago

        
      	 from {webform_submissions} ws join node na on ws.nid = na.nid join {content_field_actions} cfa on cfa.field_actions_nid = na.nid join {node} nf on nf.nid = cfa.nid join {users} u on ws.uid = u.uid where ws.uid in($friend_uid_placeholders) and cfa.delta = (select max(delta) from {content_field_actions} cfai where cfai.nid = nf.nid) order by stamp desc",
      );  
		
		
		$args = array();
    foreach($feed_queries as $type => $query){
      $query_union .= $query['query'];
      $args = array_merge($args,$friends);//needs all repeating friend uids in one array apparently :(
    }
    
    
    
    
    
    
    $count_query = "SELECT COUNT(*) FROM (" . $query_union . ") AS count_query";
    
    $feed_items = pager_query($query_union, 13, 0, $count_query, $args);//careful here, $args must work for count query and main query or this wont work.


    while($f = db_fetch_object($feed_items)){
      $item = new stdClass();
  		$item->excerpt = $f->excerpt;
      $item->src = v2_profiles_avatars_query($f->uid);
  		$item->stamp = $f->stamp;
  		$item->time_ago = $f->time_ago;
  		$items[] = $item;
    }
		?>
		
    <?php foreach ($items as $item) { ?>
      	<div class="item">
      		<span class="image">
      			<img height="42" src="<?php print $item->src; ?>" width="42" />
      		</span>
      		<?php
      			$_excerpt = $item->excerpt  . ' <em class="feed-time">' .  $item->time_ago . '</em>';
      			$_excerpt = str_replace('/user/'.$user->uid, '/user', $_excerpt);
      			$_excerpt = preg_replace('/("\/user\/)([0-9]+)(")/i', '"/user/'.$user->uid.'/friends/$2/"', $_excerpt);
      		?>
      		<span class="message">
      			<?php print $_excerpt; ?>
      		</span>
      	</div>
    <?php } ?>		
    <?php
      print theme('pager', NULL, 10, 0);
      exit;
}