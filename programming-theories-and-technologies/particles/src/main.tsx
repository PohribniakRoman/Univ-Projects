import React from 'react'
import ReactDOM from 'react-dom/client'
import './styles/main.scss'
import { App } from './App'
import { configureStore } from '@reduxjs/toolkit'
import { combinedReducer } from './reducers/combinedReducer'
import { Provider } from 'react-redux'

const store = configureStore({reducer:combinedReducer})

ReactDOM.createRoot(document.getElementById('root')!).render(
  <React.StrictMode>
    <Provider store={store}>
      <App />
    </Provider>
  </React.StrictMode>,
)
