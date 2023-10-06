const express = require('express');
const app = express();
const bodyParser = require('body-parser');
const path = require('path');

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

// Serve static files from the "public" directory
app.use(express.static(path.join(__dirname, 'public')));

// Handle GET and POST requests for "/update-location" endpoint
app.route('/update-location')
  .get((req, res) => {
    // Handle GET request here, if needed
    res.send('GET request received');
  })
  .post((req, res) => {
    // Handle POST request here
    const wifiData = req.body.wifi;
    // Process the received data as needed
    console.log('Received Wi-Fi data:', wifiData);
    res.send('Data received');
  });

// Serve the HTML file
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

// Start the server
app.listen(8081, () => {
  console.log('Server running on port 8081');
});
