// script.js
function generateMatrixInput() {
    const size = document.getElementById('size').value;
    const matrixInputDiv = document.getElementById('matrix-input');
    matrixInputDiv.innerHTML = ''; // Clear previous input fields

    if (size > 0) {
        for (let i = 0; i < size; i++) {
            for (let j = 0; j < size; j++) {
                const input = document.createElement('input');
                input.type = 'number';
                input.id = `matrix-${i}-${j}`;
                input.placeholder = `A[${i}][${j}]`;
                matrixInputDiv.appendChild(input);
            }
            matrixInputDiv.appendChild(document.createElement('br'));
        }
        matrixInputDiv.style.display = 'block';
    } else {
        matrixInputDiv.style.display = 'none';
    }
}

function matrixMultiply(A, B, N) {
    const result = Array.from({ length: N }, () => Array(N).fill(0));

    for (let i = 0; i < N; i++) {
        for (let j = 0; j < N; j++) {
            for (let k = 0; k < N; k++) {
                result[i][j] = (result[i][j] + (A[i][k] * B[k][j])) % (1e9 + 7);
            }
        }
    }

    return result;
}

function matrixPowerIterative(A, N, exp) {
    const result = Array.from({ length: N }, () => Array(N).fill(0));
    for (let i = 0; i < N; i++) result[i][i] = 1; // Identity matrix

    let base = A.slice();
    while (exp > 0) {
        if (exp % 2 === 1) {
            result = matrixMultiply(result, base, N);
        }
        base = matrixMultiply(base, base, N);
        exp = Math.floor(exp / 2);
    }

    return result;
}

function matrixPowerRecursive(A, N, exp) {
    if (exp === 0) {
        const result = Array.from({ length: N }, () => Array(N).fill(0));
        for (let i = 0; i < N; i++) result[i][i] = 1;
        return result;
    }
    if (exp === 1) return A;

    let temp = matrixPowerRecursive(A, N, Math.floor(exp / 2));
    temp = matrixMultiply(temp, temp, N);

    if (exp % 2 === 1) {
        return matrixMultiply(temp, A, N);
    }

    return temp;
}

function calculateMatrixPower() {
    const N = parseInt(document.getElementById('size').value);
    const exp = parseInt(document.getElementById('power').value);
    const method = document.getElementById('method').value;

    const A = Array.from({ length: N }, () => []);
    for (let i = 0; i < N; i++) {
        for (let j = 0; j < N; j++) {
            A[i][j] = parseInt(document.getElementById(`matrix-${i}-${j}`).value);
        }
    }

    let result;
    if (method === 'iterative') {
        result = matrixPowerIterative(A, N, exp);
    } else {
        result = matrixPowerRecursive(A, N, exp);
    }

    document.getElementById('output').textContent = result.map(row => row.join(' ')).join('\n');
    const complexity = N * N * N * Math.log(exp);
    document.getElementById('complexity').textContent = `Complexity: O(N^3 * log(exp)) ~ ${Math.round(complexity)}`;
}

document.getElementById('size').addEventListener('input', generateMatrixInput);
