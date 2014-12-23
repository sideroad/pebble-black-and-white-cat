/**
 * Welcome to Pebble.js!
 *
 * This is where you write your app.
 */

var UI = require('ui');
var Vector2 = require('vector2');

var main = new UI.Window();
main.add(
  new UI.Image({
    position: new Vector2(0, 0),
    size: new Vector2(144, 168),
    image: 'images/cat.png'
  })
);

// Hour
main.add(
  new UI.TimeText({
    position: new Vector2(-5, 30),
    size: new Vector2(50, 42),
    font: 'bitham-34-medium-numbers',
    text: '%H',
    color: 'black',
    textAlign: 'right'
  })
);

// Colon
main.add(
  new UI.TimeText({
    position: new Vector2(67, 28),
    size: new Vector2(50, 42),
    font: 'bitham-34-medium-numbers',
    text: ':',
    color: 'white',
    textAlign: 'left'
  })
);


// Minutes
main.add(
  new UI.TimeText({
    position: new Vector2(97, 31),
    size: new Vector2(50, 42),
    font: 'bitham-34-medium-numbers',
    text: '%M',
    color: 'black',
    textAlign: 'left'
  })
);

// Month
main.add(
  new UI.TimeText({
    position: new Vector2(45, 80),
    size: new Vector2(50, 42),
    font: 'gothic-28',
    text: '%b',
    color: 'white',
    textAlign: 'center'
  })
);

// Date
main.add(
  new UI.TimeText({
    position: new Vector2(45, 108),
    size: new Vector2(50, 42),
    font: 'gothic-28',
    text: '%d',
    color: 'white',
    textAlign: 'center'
  })
);

// Weekday
main.add(
  new UI.TimeText({
    position: new Vector2(80, 125),
    size: new Vector2(50, 42),
    font: 'gothic-28-bold',
    text: '%a',
    color: 'black',
    textAlign: 'right'
  })
);

main.show();
