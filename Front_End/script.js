document.addEventListener("DOMContentLoaded", function() {
    var screenWidth = window.innerWidth;
    var ctx = document.getElementById('verticalBarGraph').getContext('2d');
    var verticalBarGraph = new Chart(ctx, {
        type: 'bar',
        data: {
            labels: ['Wickets', 'Fours', 'Sixes', 'Dot Balls', 'Extras', 'Wides', 'No Balls', 'Byes'],
            datasets: [{
                label: 'Innings 1 (MUMBAI_INDIANS)',
                backgroundColor: 'rgba(255, 193, 7,  0.75)',
                borderColor: 'rgba(255, 99, 132, 1)',
                borderWidth: 1,
                data: [0.666667, 1, 1, 0.384615, 0.625, 0.5, 0.333333, 1]
            }, {
                label: 'Innings 2 (ROYAL_CHALLENGERS)',
                backgroundColor: 'rgba(240, 11, 11, 0.75)',
                borderColor: 'rgba(54, 162, 235, 1)',
                borderWidth: 1,
                data: [1, 0.666667, 0.625, 1, 1, 1, 1, 0]
            }]
        },
        options: {
            responsive: true,
            maintainAspectRatio: false,
            scales: {
                x: {
                    stacked: false,
                    ticks: {
                        color: 'white',
                        font: {
                            size: screenWidth > 600 ? 22 : 16
                        }
                    }
                },
                y: {
                    ticks: {
                        color: 'white',
                        font: {
                            size: screenWidth > 600 ? 22 : 16
                        }
                    }
                }
            },
            plugins: {
                legend: {
                    labels: {
                        color: 'white',
                        font: {
                            size: screenWidth > 600 ? 22 : 16
                        }
                    }
                }
            }
        }
    });
});
