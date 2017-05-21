// [START imports]
var FCM = require('fcm-node');
var serverKey = 'AAAAFg4y-to:APA91bGa_2cb_RVi5idQnmnoV59Olyh33oqI_p4NJk96zT0W73LTQgimFHyFvgzDui97dlMXUdGv2TetmfjlufqHpjS0v71TimYzWPekJXucCEj1-44-e-cj7CD7NXq2-fbriyfsZCxp'; //put your server key here
var fcm = new FCM(serverKey);
var firebase = require('firebase-admin');
// [END imports]

var serviceAccount = require('./service/cam-nang-lien-quan-firebase-adminsdk-9cfhy-3a1df0400c.json');
firebase.initializeApp({
  credential: firebase.credential.cert(serviceAccount),
  databaseURL: 'https://cam-nang-lien-quan.firebaseio.com'
});

function pushNotification(bodyNotification){
  // List the top 5 posts.
  // [START top_posts_query]
  //var topPostsRef = firebase.database().ref('/posts').orderByChild('starCount').limitToLast(5);
  // [END top_posts_query]

  var allUserRef = firebase.database().ref('/tokens');
  Promise.all([allUserRef.once('value')]).then(function(resp) {
    //var topPosts = resp[0].val();§
  //  var uid = postSnapshot.val().uid;
    var allUsers = resp[0].val();
    Object.keys(allUsers).forEach(function(uid) {
        var user = allUsers[uid];
        var message = { //this may vary according to the message type (single recipient, multicast, topic, et cetera)
            to: user,
            notification: {
                title: 'Cẩm nang liên quân',
                body: bodyNotification
            },
            data: {  //you can send only notification or only data(or include both)
              title: 'Cẩm nang liên quân',
              body: bodyNotification
            }
        };

        console.log(message);
        fcm.send(message, function(err, response){
            if (err) {
                console.log("Something has gone wrong!");
                console.log(err);
            } else {
                console.log("Successfully sent with response: ", response);
            }
        });
      });
  }).catch(function(error) {
    console.log('Failed to start weekly top posts emailer:', error);
  });
}

// var message = { //this may vary according to the message type (single recipient, multicast, topic, et cetera)
//     to: 'coDNY8xdLD4:APA91bFje8RiksC_NA3tyj4NC_anTn-bd3s5IzJG5iRLKYKnwLxH1oFK3t-iQPKmvAR72VBeTwkOvY6x0tc2Snd5DGjlLOqncVpkWAw0C63OkuR8n2vUQjGTLzUVn_coOnCHpbC5LHnD',
//     collapse_key: 'demo',
//
//     notification: {
//         title: 'Cam nang lien quan',
//         body: 'test2'
//     },
//     data: {  //you can send only notification or only data(or include both)
//         my_key: 'my value',
//         my_another_key: 'my another value'
//     }
// };

// fcm.send(message, function(err, response){
//     if (err) {
//         console.log("Something has gone wrong!");
//     } else {
//         console.log("Successfully sent with response: ", response);
//     }
// });
pushNotification('Ra mắt tướng mới Raz');
